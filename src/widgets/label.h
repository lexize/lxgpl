#include "../gui.h"
#include "../drawing_context.h"
#include "../font.h"

#ifndef  __LXG_WIDGET_LABEL
#define  __LXG_WIDGET_LABEL

typedef struct {
   LXGFont* font;
   int color;
   char* text;
   size_t len;
   int font_size;
   int cached_width;
   int cached_height;
   bool dirty;
} LXGLabelWidget;

void lxg_init_label_widget();

void lxg_label_get_size(LXGLabelWidget* widget, int* width_out, int* height_out);
void lxg_label_set_font_size(LXGLabelWidget* widget, int font_size);

int lxg_label_get_color(LXGLabelWidget* widget);
void lxg_label_set_color(LXGLabelWidget* widget, int color);

LXGFont* lxg_label_get_font(LXGLabelWidget* widget);
void lxg_label_set_font(LXGLabelWidget* widget, LXGFont* font);

char* lxg_label_get_text(LXGLabelWidget* widget, size_t* len_out);
void lxg_label_set_text(LXGLabelWidget* widget, char* text, size_t len);
void lxg_label_set_text_nterm(LXGLabelWidget* widget, char* text);

/**
 * Creates a label widget.
 * `widget_out` argument is optional. If it is present, it will set the variable by pointer to an LXGWidget instance bound to newly created label. */
LXGLabelWidget* lxg_label_new(LXGWidget* widget_out);

#endif//__LXG_WIDGET_LABEL
