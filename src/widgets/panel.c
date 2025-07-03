#include "panel.h"

static size_t PANEL_WIDGET_CLASS_ID;

int lxg_panel_width(LXGPanelWidget* panel) {
   return panel->width;
}

int lxg_panel_height(LXGPanelWidget* panel) {
   return panel->height;
}

bool lxg_panel_needs_redrawing(LXGPanelWidget* panel) {
   return panel->dirty || (panel->child && lxg_widget_needs_redrawing(panel->child));
}

bool lxg_panel_on_key(LXGPanelWidget* panel, int key, int state, int modifiers) {
   return panel->child && lxg_widget_on_key(panel->child, key, state, modifiers);
}

bool lxg_panel_on_char(LXGPanelWidget* panel, int scancode, int state, int modifiers) {
   return panel->child && lxg_widget_on_char(panel->child, scancode, state, modifiers);
}

struct panel_child_bounds {
   int x;
   int y;
   int width;
   int height;
};

struct panel_child_bounds lxg_panel_get_child_bounds(LXGPanelWidget* panel) {
   struct panel_child_bounds bounds = {0};
   bounds.x = panel->padding_left;
   bounds.y = panel->padding_top;
   bounds.width = panel->width - (panel->padding_left + panel->padding_right);
   bounds.height = panel->height - (panel->padding_top + panel->padding_bottom);
   return bounds;
};

bool lxg_panel_on_mouse_click(LXGPanelWidget* panel, int mouse_button, int state, int x, int y) {
   if (panel->child) {
      struct panel_child_bounds bounds = lxg_panel_get_child_bounds(panel);
      return lxg_widget_on_mouse_click(panel->child, mouse_button, state, x - bounds.x, y - bounds.y);  
   }
   return false;
}

bool lxg_panel_on_mouse_scroll(LXGPanelWidget* panel, int direction, int amount, int x, int y) {
   if (panel->child) {
      struct panel_child_bounds bounds = lxg_panel_get_child_bounds(panel);
      return lxg_widget_on_mouse_scroll(panel->child, direction, amount, x - bounds.x, y - bounds.y);  
   }
return false;
}

void lxg_panel_on_mouse_move(LXGPanelWidget* panel, int x, int y) {
   if (panel->child) {
      struct panel_child_bounds bounds = lxg_panel_get_child_bounds(panel);
      lxg_widget_on_mouse_move(panel->child, x - bounds.x, y - bounds.y);  
   }
}

void lxg_panel_accept_boundaries(LXGPanelWidget* panel, int abs_x, int abs_y, int _x, int _y, int width, int height) {
   panel->abs_x = abs_x;
   panel->abs_y = abs_y;
   if (panel->accept_adjustments) {
      panel->width = width;
      panel->height = height;
      panel->dirty = true;
   }
   if (panel->child) {
      struct panel_child_bounds bounds = lxg_panel_get_child_bounds(panel);
      lxg_widget_accept_boundaries(panel->child, abs_x + bounds.x, abs_y + bounds.y, bounds.x, bounds.y, bounds.width, bounds.height);
   }
}

void lxg_panel_get_size(LXGPanelWidget* widget, int* width_out, int* height_out) {
   if (width_out) *width_out = widget->width;
   if (height_out) *height_out = widget->height;
}

void lxg_panel_set_size(LXGPanelWidget* widget, int width, int height) {
   widget->width = width;
   widget->height = height;
   widget->dirty = true;
};

int lxg_panel_get_rounding(LXGPanelWidget* widget) {
   return widget->rounding;
}

void lxg_panel_set_rounding(LXGPanelWidget* widget, int rounding) {
   widget->rounding = rounding < 0 ? 0 : rounding;
   widget->dirty = true;
}

int lxg_panel_get_color(LXGPanelWidget* widget) {
   return widget->color;
}

void lxg_panel_set_color(LXGPanelWidget* widget, int color) {
   widget->color = color;
   widget->dirty = true;
}


LXGWidget* lxg_panel_get_child(LXGPanelWidget* widget) {
   return widget->child;
}

void lxg_panel_set_child(LXGPanelWidget* widget, LXGWidget* child) {
   widget->child = child;
   widget->dirty = true;
}

bool lxg_panel_is_cropped(LXGPanelWidget* widget) {
   return widget->crop;
}

void lxg_panel_set_cropped(LXGPanelWidget* widget, bool crop) {
   widget->crop = crop;
   widget->dirty = true;
}

void lxg_panel_get_padding(LXGPanelWidget* widget, int* padding_left_out, int* padding_right_out, int* padding_top_out, int* padding_bottom_out) {
   if (padding_left_out) *padding_left_out = widget->padding_left;
   if (padding_right_out) *padding_right_out = widget->padding_right;
   if (padding_top_out) *padding_top_out = widget->padding_top;
   if (padding_bottom_out) *padding_bottom_out = widget->padding_bottom;
}

void lxg_panel_set_padding(LXGPanelWidget* widget, int padding_left, int padding_right, int padding_top, int padding_bottom) {
   widget->padding_left = padding_left;
   widget->padding_right = padding_right;
   widget->padding_top = padding_top;
   widget->padding_bottom = padding_bottom;
   widget->dirty = true;
}


void lxg_panel_render_background(LXGPanelWidget* widget, LXGDrawCtx* ctx) {
   if (widget->rounding) {
      int line_h_width = widget->width - (widget->rounding * 2);
      int line_v_height = widget->height - (widget->rounding*2);
      int round = widget->rounding;
      lxg_draw_circle_quart(ctx, round-1, 0, widget->rounding, 2, widget->color, true); // Left upper corner
      lxg_draw_circle_quart(ctx, round+line_h_width, 0, widget->rounding, 0, widget->color, true); // Right upper corner
      lxg_draw_circle_quart(ctx, round-1, widget->height-1, widget->rounding, 3, widget->color, true); // Left lower corner
      lxg_draw_circle_quart(ctx, round+line_h_width, widget->height-1, widget->rounding, 1, widget->color, true); // Right lower corner
      lxg_draw_rectangle(ctx, round, 0, round+line_h_width, round, widget->color); // Upper center
      lxg_draw_rectangle(ctx, round, round+line_v_height, round+line_h_width, widget->height, widget->color); // Lower center
      lxg_draw_rectangle(ctx, 0, round, widget->width, round+line_v_height, widget->color); // Middle
   }
   else {
      lxg_draw_rectangle(ctx, 0, 0, widget->width, widget->height, widget->color);
   }
};

void lxg_panel_rebuild(LXGPanelWidget* widget) {
   LXGCanvas* c = widget->stencil_canvas;
   struct panel_child_bounds bounds = lxg_panel_get_child_bounds(widget);
   if (widget->crop) {
      if (widget->stencil_canvas) {
         if (c->width != widget->width || c->height != widget->height) {
            lxg_canvas_free(c);
            free(widget->stencil);
         }
         else goto crop_unchanged;
      }
      widget->stencil_canvas = lxg_canvas_new(widget->width, widget->height, LXG_CANVAS_MONO);
      widget->stencil = lxg_stencil_new(widget->stencil_canvas, widget->stencil_canvas); // Destination is the stencil itself as it used for context creation. During the render stencil destination will be changed.
      LXGDrawCtx temp_ctx = {0};
      lxg_stencil_setup_context(widget->stencil, &temp_ctx);
      lxg_panel_render_background(widget, &temp_ctx); 
   }
   else if (widget->stencil_canvas) {
      lxg_canvas_free(c);
      free(widget->stencil);
   }
   crop_unchanged:
   if (widget->child) {
      lxg_widget_accept_boundaries(widget->child, widget->abs_x + bounds.x, widget->abs_y + bounds.y,
            bounds.x, bounds.y, bounds.width, bounds.height);
   };
   widget->dirty = false;
}

void lxg_panel_render(LXGDrawCtx* ctx, LXGPanelWidget* widget) {
   bool render_child = widget->child && (lxg_widget_needs_redrawing(widget->child) || widget->dirty);
   if (widget->dirty) { 
      lxg_panel_rebuild(widget);
      lxg_panel_render_background(widget, ctx);
   }
   if (render_child) {
      LXGDrawCtx child_ctx = {0};
      if (widget->crop) {
         widget->stencil->destination = ctx;
         lxg_stencil_setup_context(widget->stencil, &child_ctx);
      }
      else child_ctx = *ctx;
      lxg_widget_render_displaced(&child_ctx, widget->child, widget->padding_left, widget->padding_top);
   }
}

LXGPanelWidget* lxg_panel_new(LXGWidget* widget_out) {
   LXGPanelWidget panel_s = {0};
   LXGPanelWidget* panel = malloc(sizeof(LXGPanelWidget));
   *panel = panel_s;
   if (widget_out) {
      widget_out->clazz = PANEL_WIDGET_CLASS_ID;
      widget_out->inst = panel;
   }
   return panel;
};

void lxg_init_panel_widget() {
   LXGWidgetClass* class = lxg_create_empty_widget_class();
   class->width = lxg_panel_width;
   class->height = lxg_panel_height;
   class->needs_redrawing = lxg_panel_needs_redrawing;
   class->on_key = lxg_panel_on_key;
   class->on_char = lxg_panel_on_char;
   class->on_mouse_click = lxg_panel_on_mouse_click;
   class->on_mouse_scroll = lxg_panel_on_mouse_scroll;
   class->on_mouse_move = lxg_panel_on_mouse_move;
   class->accept_bounds = lxg_panel_accept_boundaries;
   class->render = lxg_panel_render;
   PANEL_WIDGET_CLASS_ID = lxg_register_new_widget(class);
}
