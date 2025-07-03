#include "drawing_context.h"

void lxg_draw_ctx_set_pixel(LXGDrawCtx* ctx, int x, int y, int rgba) {
   if (ctx->setter &&
       x >= ctx->x1 && x < ctx->x2 && 
       y >= ctx->x1 && y < ctx->y2) {
      ctx->setter(ctx->userdata, x, y, rgba);
   }
}

int lxg_draw_ctx_get_pixel(LXGDrawCtx* ctx, int x, int y) {
   if (ctx->getter &&
       x >= ctx->x1 && x < ctx->x2 && 
       y >= ctx->y1 && y < ctx->y2) {
      return ctx->getter(ctx->userdata, x, y);
   }
   return 0;
}
