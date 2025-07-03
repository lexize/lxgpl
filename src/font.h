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

#endif
