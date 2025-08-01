#define LXG_STRIP_PREFIX

#include "canvas.h"
#include "shapes.h"
#include "font.h"
#include <assert.h>
#include "math_utils.h"
#include "colors.h"
#include "gui.h"
#include "widgets/panel.h"
#include "widgets/label.h"
#include "curves.h"

void rgba_to_ppm(Canvas* data, int width, int height) {
   printf("P3 %d %d 255", width, height);
   for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
         ARGB argb = int_to_argb(lxg_canvas_get_pixel(data, x, y));
         printf(" %hhu %hhu %hhu", argb.b, argb.g, argb.r);
      }
   }
}

void draw_triangle_uv(LXGDrawCtx* ctx, int x, int y, uint16_t pA, uint16_t pB, uint16_t pC) {
   ABGR abgr = {
      .a = 255,
      .r = (uint8_t)(pA >> 8),
      .g = (uint8_t)(pB >> 8),
      .b = (uint8_t)(pC >> 8),
   };
   ARGB argb = *(ARGB*)(&abgr);
   int color = argb_to_int(argb);
   ctx->setter(ctx->userdata, x, y, color);
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
   Vec2I tA = {.x = 0, .y = 0};
   Vec2I tB = {.x = 0, .y = 50};
   Vec2I tC = {.x = 50, .y = 50};
   Vec2I tD = {.x = 50, .y = 0};
   lxg_draw_rectangle(ctx, 0, 0, 50, 50, 0xFFAAAAFF);
   LXGTrianglePainter painter = {
      .userdata = ctx,
      .paint = draw_triangle_uv
   };
   lxg_draw_triangle_textured(&painter, tA, tB, tC);
   lxg_draw_triangle_textured(&painter, tC, tD, tA);
   Vec2F tAF = {0,   0};
   Vec2F tBF = {0,   50.f};
   Vec2F tCF = {50.f, 50.f};
   Vec2F tDF = {50.f, 0};
   Vec2F prevP = tAF;
   for (int i = 0; i < 10; i++) {
      float t = i / 9.f;
      Vec2F p = cubic_bezier_point_vec2f(tAF, tBF, tCF, tDF, t);
      Vec2I p1 = {(int)prevP.x, (int)prevP.y};
      Vec2I p2 = {(int)p.x, (int)p.y};
      lxg_draw_line(ctx, p1.x, p1.y, p2.x, p2.y, 0xFFFFAAFF);
      lxg_draw_circle(ctx, p2.x, p2.y, 3, 0xFFFFAAFF, true);
      prevP = p;
   }

   rgba_to_ppm(canvas, 300, 300);
   canvas_free(canvas);
}
