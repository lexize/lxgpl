#include "shapes.h"
#include "misc.h"

void lxg_draw_circle(LXGDrawCtx* ctx, int x, int y, int radius, int color, bool fill) {
   if (!ctx->setter) return;
   if (radius == 0) return;
   lxg_draw_circle_quart(ctx, x, y - radius, radius, 0, color, fill);
   lxg_draw_circle_quart(ctx, x, y + (radius-1), radius, 1, color, fill);
   lxg_draw_circle_quart(ctx, x-1, y - radius, radius, 2, color, fill);
   lxg_draw_circle_quart(ctx, x-1, y + (radius-1), radius, 3, color, fill);
}

void lxg_draw_circle_quart(LXGDrawCtx* ctx, int x, int y, int radius, int rot, int color, bool fill) {
   if (!ctx->setter) return;
   if (radius == 0) return;
   int radius_sq = radius * radius;
   int cY = 0;
   int mulY = rot % 2 == 0 ? 1 : -1;
   int mulX = (rot / 2) % 2 == 0 ? 1 : -1;
   int xS[radius];
   for (int cX = 0; cX < radius; cX++) {
      int h = radius - cY;
      if ((cX * cX) + (h * h - 1) > radius_sq) {
         cY++;
      }
      if (cX >= radius - cY) break;
      ctx->setter(ctx->userdata, x + (cX * mulX), y + (cY * mulY), color);
      ctx->setter(ctx->userdata, x + ((radius - cY - 1) * mulX), y + ((radius - cX - 1) * mulY), color);
      xS[cY] = cX;
      xS[(radius - cX - 1)] = (radius - cY - 1);
   }

   if (fill) {
      for (int cY = 1; cY < radius; cY++) {
         int dX = xS[cY];
         for (int cX = 0; cX < dX; cX++) {
            ctx->setter(ctx->userdata, x + (cX * mulX), y + (cY * mulY), color);
         }
      }
   }
}


void lxg_draw_rectangle(LXGDrawCtx* ctx, int x1, int y1, int x2, int y2, int color) {
   if (!ctx->setter) return;
   int_swap_minmax(&x1, &x2);
   int_swap_minmax(&y1, &y2);
   
   if (x1 < ctx->x1) x1 = ctx->x1;
   if (x2 > ctx->x2) x2 = ctx->x2;
   if (y1 < ctx->y1) y1 = ctx->y1;
   if (y2 > ctx->y2) y2 = ctx->y2;
   
   for (int y = y1; y < y2; y++) {
      for (int x = x1; x < x2; x++) {
         ctx->setter(ctx->userdata, x, y, color);
      }
   }
}

void lxg_draw_line(LXGDrawCtx* ctx, int x1, int y1, int x2, int y2, int color) {
   if (!ctx->setter) return;
   int_swap_minmax(&x1, &x2);
   int_swap_minmax(&y1, &y2);
   
   int xDiff = x2 - x1;
   int yDiff = y2 - y1;
   if (xDiff == 0) lxg_draw_rectangle(ctx, x1, y1, x1 + 1, y2, color);
   else if (yDiff == 0) lxg_draw_rectangle(ctx, x1, y1, x2, y1 + 1, color);
   else {
      int steps = int_min(xDiff, yDiff);
      int xStep = xDiff / steps;
      int yStep = yDiff / steps;
      int cX = x1;
      int cY = y1;
      int lastStep = steps - 1;
      for (int step = 0; step < steps; step ++) {
         int nX;
         int nY;
         if (step == lastStep) {
            nX = x2;
            nY = y2;
         }
         else {
            nX = cX + xStep;
            nY = cY + yStep;
         }
         lxg_draw_rectangle(ctx, cX, cY, nX, nY, color);
         cX = nX;
         cY = nY;
      }
   }
}
