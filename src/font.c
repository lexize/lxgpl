#include <assert.h>
#include "font.h"
#include "string_builder.h"
#include "string_utils.h"
#include "da.h"
#include "misc.h"
#include <stdint.h>
#include <locale.h>

static FT_Library FREETYPE;

void lxg_font_init() {
   setlocale(LC_ALL, "");
   FT_Error error;

   error = FT_Init_FreeType(&FREETYPE);
   if (error) {
      printf("Unable to initialize FreeType: %s", FT_Error_String(error));
      abort();
   }
}

LXGFont* lxg_font_load(char* path) {
   FT_Face face;
   FT_Error error;
   if (path[0] == '/') { // Trying to load as a global path.
      error = FT_New_Face(FREETYPE, path, 0, &face);
      if (error) return NULL;
      LXGFont* f = malloc(sizeof(LXGFont));
      f->face = face;
      FT_Select_Charmap(face, FT_ENCODING_UNICODE);
      return f;
   }
   else {
      StringBuilder sb = {0};
      char* data_folders = getenv("XDG_DATA_DIRS");
      if (data_folders) {
         struct StringSplit paths = string_split(data_folders, ':');
         for (size_t i = 0; i < paths.count; i++) {
            char* data_dir = paths.items[i];
            sb.count = 0;
            sb_append(&sb, data_dir);
            sb_append(&sb, "/fonts/");
            sb_append(&sb, path);
            da_append(&sb, 0);

            error = FT_New_Face(FREETYPE, sb.items, 0, &face);
            if (!error || error != FT_Err_Cannot_Open_Resource) break;
         }
         free(paths.items);
         if (sb.items) free(sb.items);
         if (!error) {
            LXGFont* f = malloc(sizeof(LXGFont));
            f->face = face;
            FT_Select_Charmap(face, FT_ENCODING_UNICODE);
            return f;
         }
      }
      return NULL;
   }
}

int lxg_get_str_dimensions(LXGFont* font, int font_size, char* str, LXGTextDimensions* text_dimensions) {
   return lxg_get_str_dimensions_buf(font, font_size, str, strlen(str), text_dimensions);
}

int lxg_get_str_dimensions_buf(LXGFont* font, int font_size, char* str, size_t len, LXGTextDimensions* text_dimensions) {
   LXGTextPenContext ctx = {
      .pen_x = 0,
      .pen_y = 0,
      .font_size = font_size,
      .font = font,
      .space_size = font_size,
      .tab_size = font_size * 3,
      .dpi = 100,
   };

   return lxg_get_str_dimensions_ex(str, len, &ctx, text_dimensions);
}

int lxg_get_str_dimensions_ex(char* str, size_t len, LXGTextPenContext* ctx, LXGTextDimensions* dimensions) {
   LXGFont* font = ctx->font;
   bool success = lxg_set_font_size(font, ctx->font_size);
   if (!success) return LXG_INVALID_FONT_SIZE;
   int prev_char;
   int baseline_height = lxg_get_baseline_height(font);
   bool use_kerning = lxg_font_has_kerning(font);
   for (size_t i = 0; i < len; i++) {
      int c = lxg_read_unicode(&str[i], len - i, &i);
      if (c == -1) continue;
      switch (c) {
         case '\n':
            prev_char = 0;
            ctx->pen_x = ctx->base_x;
            ctx->pen_y += baseline_height;
            continue;
         case ' ':
            prev_char = 0;
            ctx->pen_x += ctx->space_size;
            continue;
         case '\t':
            prev_char = 0;
            ctx->pen_x += ctx->tab_size;
            continue;
      }
      FT_GlyphSlot glyph;
      if (lxg_font_get_glyph(font, c, &glyph)) {
         if (prev_char && use_kerning) {
            int kernX;
            if (lxg_font_get_kerning(font, prev_char, c, &kernX, NULL)) ctx->pen_x += kernX;
         }
         ctx->pen_x += (glyph->advance.x >> 6);
         if (ctx->pen_x > dimensions->width) dimensions->width = ctx->pen_x;
         if (ctx->pen_y + baseline_height > dimensions->height) dimensions->height = ctx->pen_y + baseline_height;
      }
   }
   return 0;
}

int lxg_render_text(LXGDrawCtx* dctx, int x, int y, LXGFont* font, int font_size, char* str, int color) {
   return lxg_render_text_buf(dctx, x, y, font, font_size, str, strlen(str), color);
}
int lxg_render_text_buf(LXGDrawCtx* dctx, int x, int y, LXGFont* font, int font_size, char* str, size_t len, int color) {
   LXGTextPenContext ctx = {
      .base_x = x,
      .pen_x = x,
      .pen_y = y,
      .font_size = font_size,
      .font = font,
      .space_size = font_size,
      .tab_size = font_size * 3,
      .dpi = 100,
   };

   return lxg_render_text_ex(dctx, str, len, color, &ctx);
}

void lxg_render_freetype_glyph(LXGDrawCtx* dctx, FT_GlyphSlot glyph, int x, int y, int color) {
   FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);
   FT_Bitmap bmp = glyph->bitmap;
   ABGR base_color = *(ABGR*)(&color);
   for (size_t bY = 0; bY < bmp.rows; bY++) {
      for (size_t bX = 0; bX < bmp.width; bX++) {
         ABGR out_color = {0};
         int weight = bmp.buffer[bX + (bY * bmp.width)];
         out_color.r = base_color.r;
         out_color.g = base_color.g;
         out_color.b = base_color.b;
         out_color.a = (base_color.a * weight) / 0xFF;
         lxg_draw_ctx_set_pixel(dctx, x + bX, y + bY, *(int*)(&out_color));
      }
   }
}

const char NON_UNICODE_MASK = 0b10000000;
const char SEQUENCE_CONTINUATION_MASK = 0b11000000;
const char CONTINUED_SEQUENCE_MASK = 0b00111111;
const char UNICODE_2_OCT_MASK = 0b11100000;
const char UNICODE_3_OCT_MASK = 0b11110000;
const char UNICODE_4_OCT_MASK = 0b11111000;

const char NON_UNICODE = 0b00000000;
const char SEQUENCE_CONTINUATION = 0b10000000;
const char UNICODE_2_OCT = 0b11000000;
const char UNICODE_3_OCT = 0b11100000;
const char UNICODE_4_OCT = 0b11110000;

int lxg_read_unicode(char* str, size_t len, int* index) {
   char c = str[0];
   int octets;
   char mask;
   if ((c & NON_UNICODE_MASK) == NON_UNICODE) return c; 
   else if ((c & SEQUENCE_CONTINUATION_MASK) == SEQUENCE_CONTINUATION) return -1;
   else if ((c & UNICODE_2_OCT_MASK) == UNICODE_2_OCT) { octets = 1; mask = ~UNICODE_2_OCT_MASK; }
   else if ((c & UNICODE_3_OCT_MASK) == UNICODE_3_OCT) { octets = 2; mask = ~UNICODE_3_OCT_MASK; }
   else if ((c & UNICODE_4_OCT_MASK) == UNICODE_4_OCT) { octets = 3; mask = ~UNICODE_4_OCT_MASK; }
   int seq = (c & mask);
   for (int i = 0; i < octets; i++) {
      int current_c = str[i+1];
      if ((current_c & SEQUENCE_CONTINUATION_MASK) != SEQUENCE_CONTINUATION) return -1;
      int m = (current_c & CONTINUED_SEQUENCE_MASK);
      seq = (seq << 6) | m;
   }
   *index += octets;
   return seq;
}

uint32_t lxg_font_get_char_index(LXGFont* font, int scancode) {
   return FT_Get_Char_Index(font->face, scancode);
}

bool lxg_font_has_kerning(LXGFont* font) {
   return FT_HAS_KERNING(font->face);
}

bool lxg_font_get_glyph(LXGFont* font, int scancode, FT_GlyphSlot* glyph_out) {
   uint32_t char_index = FT_Get_Char_Index(font->face, scancode);
   if (!char_index) return false;
   if (FT_Load_Glyph(font->face, char_index, 0)) return false;
   *glyph_out = font->face->glyph;
   return true;
}

bool lxg_font_get_kerning(LXGFont* font, int prev_scancode, int cur_scancode, int* kern_x_out, int* kern_y_out) {
   uint32_t char1 = FT_Get_Char_Index(font->face, prev_scancode);
   uint32_t char2 = FT_Get_Char_Index(font->face, cur_scancode);
   FT_Vector kern;
   if (!FT_Get_Kerning(font->face, char1, char2, FT_KERNING_UNFITTED, &kern)) {
      if (kern_x_out) *kern_x_out = kern.x >> 6;
      if (kern_y_out) *kern_y_out = kern.y >> 6;
      return true;
   }
   return false;
}

int lxg_get_baseline_height(LXGFont* font) {
   FT_Size_Metrics metrics = font->face->size->metrics;
   return ((metrics.ascender - metrics.descender) >> 6);
}

bool lxg_set_font_size(LXGFont* font, int font_size) {
   return !FT_Set_Char_Size(font->face, font_size << 6, font_size << 6, 100, 100);
}

int lxg_render_text_ex(LXGDrawCtx* dctx, char* str, size_t len, int color, LXGTextPenContext* ctx) {
   LXGFont* font = ctx->font;
   bool success = lxg_set_font_size(font, ctx->font_size);
   if (!success) return LXG_INVALID_FONT_SIZE;
   int prev_char;
   int baseline_height = lxg_get_baseline_height(font);
   bool use_kerning = lxg_font_has_kerning(font);
   for (size_t i = 0; i < len; i++) {
      int c = lxg_read_unicode(&str[i], len - i, &i);
      if (c == -1) continue;
      switch (c) {
         case '\n':
            prev_char = 0;
            ctx->pen_x = ctx->base_x;
            ctx->pen_y += baseline_height;
            continue;
         case ' ':
            prev_char = 0;
            ctx->pen_x += ctx->space_size;
            continue;
         case '\t':
            prev_char = 0;
            ctx->pen_x += ctx->tab_size;
            continue;
      }
      FT_GlyphSlot glyph;
      if (lxg_font_get_glyph(font, c, &glyph)) {   
         if (prev_char && use_kerning) {
            int kernX;
            if (lxg_font_get_kerning(font, prev_char, c, &kernX, NULL)) ctx->pen_x += kernX;
         }
         lxg_render_freetype_glyph(dctx, glyph, ctx->pen_x + glyph->bitmap_left, ctx->pen_y - glyph->bitmap_top + ctx->font_size, color);
         prev_char = c;
         ctx->pen_x += (glyph->advance.x >> 6);
      }
   }

   return 0;

}
