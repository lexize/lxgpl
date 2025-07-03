#define LXGUI_STRIP_PREFIX

#include "canvas.h"
#include "shapes.h"
#include "font.h"
#include <assert.h>
#include "math_utils.h"
#include "colors.h"
#include "gui.h"
#include "widgets/panel.h"
#include "widgets/label.h"

void rgba_to_ppm(Canvas* data, int width, int height) {
   printf("P3 %d %d 255", width, height);
   for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
         ARGB argb = int_to_argb(lxg_canvas_get_pixel(data, x, y));
         printf(" %hhu %hhu %hhu", argb.b, argb.g, argb.r);
      }
   }
}

int main() {
   lxg_font_init();
   lxg_init();
   lxg_init_panel_widget();
   lxg_init_label_widget();
   Canvas* canvas = canvas_new(300, 300, LXG_CANVAS_ARGB);
   DrawCtx* ctx = canvas_create_context(canvas);
   draw_rectangle(ctx, 100, 100, 200, 200, 0xFFAAAAFF);
   draw_circle(ctx, 150, 150, 50, 0x00FF0080, true);
   LXGWidget panel_widget = {0};
   LXGPanelWidget* panel = lxg_panel_new(&panel_widget);
   LXGWidget subpanel_widget = {0};
   LXGPanelWidget* subpanel = lxg_panel_new(&subpanel_widget);
   
   lxg_panel_set_rounding(subpanel, 8);
   lxg_panel_set_color(subpanel, 0xAAFFAAFF);
   subpanel->accept_adjustments = true; 

   lxg_panel_set_rounding(panel, 8);
   lxg_panel_set_size(panel, 200, 90);
   lxg_panel_set_color(panel, 0xFFAAAAFF);
   lxg_panel_set_child(panel, &subpanel_widget);
   lxg_panel_set_cropped(panel, true);
   lxg_panel_set_padding(panel, 1, 1, 1, 1);

   lxg_widget_render(ctx, &panel_widget);

   rgba_to_ppm(canvas, 300, 300);
   canvas_free(canvas);
}
