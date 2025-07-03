#include "../gui.h"
#include "../canvas.h"
#include "../shapes.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef  __LXG_WIDGET_PANEL
#define  __LXG_WIDGET_PANEL

typedef enum {
   LXG_PANEL_CROP = 0,
   LXG_PANEL_ADJUST = 1
} LXGPanelChildPosPolicy;

typedef struct {
   LXGWidget* child;
   LXGCanvas* stencil_canvas;
   LXGStencil* stencil;
   int color;
   int rounding;
   unsigned int width;
   unsigned int height;
   bool accept_adjustments;
   bool crop;
   bool dirty;
   int abs_x;
   int abs_y;
   int padding_left;
   int padding_right;
   int padding_top;
   int padding_bottom;
} LXGPanelWidget;

/**
 * Creates a panel widget.
 * `widget_out` argument is optional. If it is present, it will set the variable by pointer to an LXGWidget instance bound to newly created panel. */
LXGPanelWidget* lxg_panel_new(LXGWidget* widget_out);

void lxg_panel_get_size(LXGPanelWidget* widget, int* width_out, int* height_out);
void lxg_panel_set_size(LXGPanelWidget* widget, int width, int height);

void lxg_panel_set_rounding(LXGPanelWidget* widget, int rounding);
int lxg_panel_get_rounding(LXGPanelWidget* widget);

void lxg_panel_rebuild(LXGPanelWidget* widget);

int lxg_panel_get_color(LXGPanelWidget* widget);
void lxg_panel_set_color(LXGPanelWidget* widget, int color);

LXGWidget* lxg_panel_get_child(LXGPanelWidget* widget);
void lxg_panel_set_child(LXGPanelWidget* widget, LXGWidget* child);

bool lxg_panel_is_cropped(LXGPanelWidget* widget);
void lxg_panel_set_cropped(LXGPanelWidget* widget, bool crop);

void lxg_panel_get_padding(LXGPanelWidget* widget, int* padding_left_out, int* padding_right_out, int* padding_top_out, int* padding_bottom_out);
void lxg_panel_set_padding(LXGPanelWidget* widget, int padding_left, int padding_right, int padding_top, int padding_bottom);

void lxg_init_panel_widget();

#endif//__LXG_WIDGET_PANEL
