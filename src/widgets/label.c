#include "label.h"

static size_t LABEL_WIDGET_CLASS_ID;

void lxg_label_recalc_bounds(LXGLabelWidget* widget) {
   if (widget->font && widget->text) {
      LXGTextDimensions dims = {0};
      if (!lxg_get_str_dimensions_buf(widget->font, widget->font_size, widget->text, widget->len, &dims)) {
         widget->cached_width = dims.width;
         widget->cached_height = dims.height;
         widget->dirty = false;
         return;
      }
   }
   widget->cached_width = 0;
   widget->cached_height = 0;
   widget->dirty = false;
}

void lxg_label_get_size(LXGLabelWidget* widget, int* width_out, int* height_out) {
   if (widget->dirty) lxg_label_recalc_bounds(widget);
   if (width_out) *width_out = widget->cached_width;
   if (height_out) *height_out = widget->cached_height;
}

void lxg_label_set_font_size(LXGLabelWidget* widget, int font_size) {
   widget->font_size = font_size;
   widget->dirty = true;
}

int lxg_label_get_color(LXGLabelWidget* widget) {
   return widget->color;
}

void lxg_label_set_color(LXGLabelWidget* widget, int color) {
   widget->color = color;
}

LXGFont* lxg_label_get_font(LXGLabelWidget* widget) {
   return widget->font;
}

void lxg_label_set_font(LXGLabelWidget* widget, LXGFont* font) {
   widget->font = font;
   widget->dirty = true;
}

char* lxg_label_get_text(LXGLabelWidget* widget, size_t* len_out) {
   if (len_out) *len_out = widget->len;
   return widget->text;
}

void lxg_label_set_text(LXGLabelWidget* widget, char* text, size_t len) {
   widget->text = text;
   widget->len = len;
   widget->dirty = true;
}

void lxg_label_set_text_nterm(LXGLabelWidget* widget, char* text) {
   if (text) lxg_label_set_text(widget, text, strlen(text));
   else lxg_label_set_text(widget, NULL, 0);
}

int lxg_label_width(LXGLabelWidget* widget) {
   int width;
   lxg_label_get_size(widget, &width, NULL);
   return width;
}

int lxg_label_height(LXGLabelWidget* widget) {
   int height;
   lxg_label_get_size(widget, NULL, &height);
   return height;
}

bool lxg_label_needs_redrawing(LXGLabelWidget* widget) {
   return widget->dirty;
}

void lxg_label_render(LXGDrawCtx* ctx, LXGLabelWidget* widget) {
   if (widget->dirty) lxg_label_recalc_bounds(widget);
   lxg_render_text_buf(ctx, 0, 0, widget->font, widget->font_size, widget->text, widget->len, widget->color);
}

LXGLabelWidget* lxg_label_new(LXGWidget* widget_out) {
   LXGLabelWidget label_s = {.font_size = 12, .color = -1};
   LXGLabelWidget* label = malloc(sizeof(LXGLabelWidget));
   *label = label_s;
   if (widget_out) {
      widget_out->clazz = LABEL_WIDGET_CLASS_ID;
      widget_out->inst = label;
   }
   return label;
}

void lxg_init_label_widget() {
   LXGWidgetClass* class = lxg_create_empty_widget_class();
   class->width = lxg_label_width;
   class->height = lxg_label_height;
   class->needs_redrawing = lxg_label_needs_redrawing;
   class->render = lxg_label_render;
   LABEL_WIDGET_CLASS_ID = lxg_register_new_widget(class);
}
