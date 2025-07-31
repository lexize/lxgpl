#ifndef LXG_FONT
#define LXG_FONT

#include <freetype/freetype.h>
#include "drawing_context.h"
#include <stdbool.h>
#include <stdint.h>
#include "colors.h"

enum LXGTextError_e {
   LXG_INVALID_FONT_SIZE = 1,
};

typedef enum LXGTextError_e LXGTextError;

struct LXGTextDimensions_s {
   int width;
   int height;
};


struct LXGFont_s {
   FT_Face face;
};

struct LXGTextPenContext_s {
   int base_x;
   int pen_x;
   int pen_y;
   int font_size;
   int dpi;
   int space_size;
   int tab_size;
   int linegap;
   struct LXGFont_s* font;
};

typedef struct LXGTextDimensions_s LXGTextDimensions;
typedef struct LXGFont_s LXGFont;
typedef struct LXGTextPenContext_s LXGTextPenContext;

void lxg_font_init();

LXGFont* lxg_font_load(char* path);

int lxg_get_str_dimensions(LXGFont* font, int font_size, char* str, LXGTextDimensions* text_dimensions);
int lxg_get_str_dimensions_buf(LXGFont* font, int font_size, char* str, size_t len, LXGTextDimensions* text_dimensions);
int lxg_get_str_dimensions_ex(char* str, size_t len, LXGTextPenContext* ctx, LXGTextDimensions* text_dimensions);

int lxg_render_text(LXGDrawCtx* dctx, int x, int y, LXGFont* font, int font_size, char* str, int color);
int lxg_render_text_buf(LXGDrawCtx* dctx, int x, int y, LXGFont* font, int font_size, char* str, size_t len, int color);
int lxg_render_text_ex(LXGDrawCtx* dctx, char* str, size_t len, int color, LXGTextPenContext* ctx);


int lxg_read_unicode(char* str, size_t len, int* index);

bool lxg_font_has_kerning(LXGFont* font);

uint32_t lxg_font_get_char_index(LXGFont* font, int scancode);
bool lxg_font_get_glyph(LXGFont* font, int scancode, FT_GlyphSlot* glyph_out);
bool lxg_font_get_kerning(LXGFont* font, int prev_scancode, int cur_scancode, int* kern_x_out, int* kern_y_out);
int lxg_get_baseline_height(LXGFont* font);
bool lxg_set_font_size(LXGFont* font, int font_size);

void lxg_render_freetype_glyph(LXGDrawCtx* dctx, FT_GlyphSlot glyph, int x, int y, int color);

#ifdef LXG_STRIP_PREFIX
#define TextDimensions LXGTextDimensions
#define Font LXGFont
#define TextPenContext LXGTextPenContext

#define font_load lxg_font_load
#define get_str_dimensions lxg_get_str_dimensions
#define get_str_dimensions_buf lxg_get_str_dimensions_buf
#define get_str_dimensions_ex lxg_get_str_dimensions_ex

#define render_text lxg_render_text
#define render_text_buf lxg_render_text_buf
#define render_text_ex lxg_render_text_ex

#define read_unicode lxg_read_unicode
#define font_has_kerning lxg_font_has_kerning

#define font_get_char_index lxg_font_get_char_index
#define font_get_glyph lxg_font_get_glyph
#define font_get_kerning lxg_font_get_kerning
#define get_baseline_height lxg_get_baseline_height
#define set_font_size lxg_set_font_size

#define render_freetype_glyph lxg_render_freetype_glyph
#endif

#endif
