#include "colors.h"
#include "canvas.h"

size_t lxg_canvas_pixels_size(int pixels, LXGCanvasColorMode mode) {
   switch (mode) {
      default:
      case LXG_CANVAS_ARGB:
      case LXG_CANVAS_ABGR:
      case LXG_CANVAS_RGBA:
      case LXG_CANVAS_BGRA:
         return pixels * 4;
      case LXG_CANVAS_RGB:
      case LXG_CANVAS_BGR:
         return pixels * 3;
      case LXG_CANVAS_GRAY_TRANSPARENT:
         return 2;
      case LXG_CANVAS_GRAY_OPAQUE:
      case LXG_CANVAS_GRAY:
         return pixels;
      case LXG_CANVAS_MONO:
         int additional_byte = pixels % 8 > 0;
         return (pixels / 8) + additional_byte;
   }
}

size_t lxg_canvas_pixel_pointer(int pixel, LXGCanvasColorMode mode) {
   switch (mode) {
      default:
      case LXG_CANVAS_ARGB:
      case LXG_CANVAS_ABGR:
      case LXG_CANVAS_RGBA:
      case LXG_CANVAS_BGRA:
         return pixel * 4;
      case LXG_CANVAS_RGB:
      case LXG_CANVAS_BGR:
         return pixel * 3;
      case LXG_CANVAS_GRAY_TRANSPARENT:
         return pixel * 2;
      case LXG_CANVAS_GRAY_OPAQUE:
      case LXG_CANVAS_GRAY:
         return pixel;
      case LXG_CANVAS_MONO:
         return pixel / 8;
   }
}

LXGCanvas* lxg_canvas_new(unsigned int width, unsigned int height, LXGCanvasColorMode mode) {
   LXGCanvas* canvas = malloc(sizeof(LXGCanvas));
   canvas->data = calloc(lxg_canvas_pixels_size(width * height, mode), 1);
   canvas->width = width;
   canvas->height = height;
   canvas->mode = mode;
   return canvas;
}

int lxg_canvas_get_pixel(LXGCanvas* canvas, int x, int y) {
   int pix_base = (y * canvas->width) + x;
   int pixel = lxg_canvas_pixel_pointer(pix_base, canvas->mode);
   void* p = canvas->data + pixel;
   ARGB argb;
   switch(canvas->mode) {
      default:
      case LXG_CANVAS_ARGB:
         return *(int*)p;
      case LXG_CANVAS_ABGR:
         return argb_to_int(abgr_to_argb(*(ABGR*)p));
      case LXG_CANVAS_RGBA:
         return argb_to_int(rgba_to_argb(*(RGBA*)p));
      case LXG_CANVAS_BGRA:
         return argb_to_int(bgra_to_argb(*(BGRA*)p));
      case LXG_CANVAS_RGB:
         return argb_to_int(rgb_to_argb(*(RGB*)p));
      case LXG_CANVAS_BGR:
         return argb_to_int(bgr_to_argb(*(BGR*)p));
      case LXG_CANVAS_GRAY:
      case LXG_CANVAS_GRAY_OPAQUE:
         uint8_t grayscale = *(uint8_t*)p;
         argb.r = grayscale;
         argb.g = grayscale;
         argb.b = grayscale;
         argb.a = canvas->mode != LXG_CANVAS_GRAY_OPAQUE && grayscale == 0 ? 0 : 0xFF;
         return argb_to_int(argb);
      case LXG_CANVAS_GRAY_TRANSPARENT:
         RG rg = *(RG*)p;
         argb.r = rg.r;
         argb.g = rg.r;
         argb.b = rg.r;
         argb.a = rg.g;
         return argb_to_int(argb);
      case LXG_CANVAS_MONO:
         int shift = pix_base % 8;
         uint8_t pix = *(uint8_t*)p;
         int color = (pix >> shift) & 0b1;
         argb.r = color ? 0xFF : 0;
         argb.g = color ? 0xFF : 0;
         argb.b = color ? 0xFF : 0;
         argb.a = color ? 0xFF : 0;
         return argb_to_int(argb);
   }
}

void lxg_canvas_set_pixel(LXGCanvas* canvas, int x, int y, int color) {
   ARGB a = int_to_argb(lxg_canvas_get_pixel(canvas, x, y));
   ARGB b = int_to_argb(color);
   ARGB result = argb_blend(a, b);
   int pix_base = (y * canvas->width) + x;
   int pixel = lxg_canvas_pixel_pointer(pix_base, canvas->mode);
   void* p = canvas->data + pixel;
   switch (canvas->mode) {
      case LXG_CANVAS_ARGB:
         *(ARGB*)p = result;
         break;
      case LXG_CANVAS_ABGR:
         *(ABGR*)p = argb_to_abgr(result);
         break;
      case LXG_CANVAS_RGBA:
         *(RGBA*)p = argb_to_rgba(result);
         break;
      case LXG_CANVAS_BGRA:
         *(BGRA*)p = argb_to_bgra(result);
         break;
      case LXG_CANVAS_RGB:
         *(RGB*) p = argb_to_rgb(result);
         break;
      case LXG_CANVAS_BGR:
         *(BGR*) p = argb_to_bgr(result);
         break;
      case LXG_CANVAS_GRAY:
      case LXG_CANVAS_GRAY_OPAQUE:
         *(uint8_t*)p = (result.r + result.g + result.b) / 3;
         break;
      case LXG_CANVAS_GRAY_TRANSPARENT:
         RG rg = {
            .r = (result.r + result.g + result.b) / 3,
            .g = result.a
         };
         *(RG*)p = rg;
         break;
      case LXG_CANVAS_MONO:
         int shift = pix_base % 8;
         int bit = (result.a && (result.r || result.g || result.b)) << shift;
         *(uint8_t*)p |= bit;

   }
}

LXGDrawCtx* lxg_canvas_create_context(LXGCanvas* canvas) {
   LXGDrawCtx* context = malloc(sizeof(LXGDrawCtx));
   lxg_canvas_setup_context(canvas, context);
   return context;
}

void lxg_canvas_setup_context(LXGCanvas* canvas, LXGDrawCtx* context) {
   context->x1 = 0;
   context->y1 = 0;
   context->x2 = canvas->width;
   context->y2 = canvas->height;
   context->userdata = canvas;
   context->setter = &lxg_canvas_set_pixel;
   context->getter = &lxg_canvas_get_pixel;
}

LXGStencil* lxg_stencil_new(LXGDrawCtx* source, LXGDrawCtx* destination) {
   LXGStencil* stencil = malloc(sizeof(LXGStencil));
   stencil->source = source;
   stencil->destination = destination;
   return stencil;
}

int lxg_stencil_get_pixel(LXGStencil* stencil, int x, int y) {
   return lxg_draw_ctx_get_pixel(stencil->destination, x, y);
}

void lxg_stencil_set_pixel(LXGStencil* stencil, int x, int y, int color) {
   if (lxg_stencil_get_pixel(stencil, x, y)) lxg_draw_ctx_set_pixel(stencil->destination, x, y, color);
}

LXGDrawCtx* lxg_stencil_create_context(LXGStencil* stencil) {
   LXGDrawCtx* context = malloc(sizeof(LXGDrawCtx));
   lxg_stencil_setup_context(stencil, context);
   return context;
}

void lxg_stencil_setup_context(LXGStencil* stencil, LXGDrawCtx* context) {
   context->x1 = stencil->destination->x1;
   context->y1 = stencil->destination->y1;
   context->x2 = stencil->destination->x2;
   context->y2 = stencil->destination->x2;
   context->userdata = stencil;
   context->setter = &lxg_stencil_set_pixel;
   context->getter = &lxg_stencil_get_pixel;
}

LXGDrawProxy* lxg_draw_proxy_new(int x, int y, unsigned int width, unsigned int height, LXGDrawCtx* destination){
   LXGDrawProxy* proxy = malloc(sizeof(LXGDrawProxy));
   proxy->x = x;
   proxy->y = y;
   proxy->width = width;
   proxy->height = height;
   proxy->destination = destination;
}

int lxg_draw_proxy_get_pixel(LXGDrawProxy* proxy, int x, int y) {
   if (x < 0 || x >= proxy->width || y < 0 || y >= proxy->height) return 0;
   return lxg_draw_ctx_get_pixel(proxy->destination, x + proxy->x, y + proxy->y);
}

void lxg_draw_proxy_set_pixel(LXGDrawProxy* proxy, int x, int y, int color) {
   if (x < 0 || x >= proxy->width || y < 0 || y >= proxy->height) return;
   lxg_draw_ctx_set_pixel(proxy->destination, x + proxy->x, y + proxy->y, color);
}

LXGDrawCtx* lxg_draw_proxy_create_context(LXGDrawProxy* proxy) {
   LXGDrawCtx* context = malloc(sizeof(LXGDrawCtx));
   lxg_draw_proxy_setup_context(proxy, context);
   return context;
}

void lxg_draw_proxy_setup_context(LXGDrawProxy* proxy, LXGDrawCtx* context) {
   context->x1 = 0;
   context->y1 = 0;
   context->x2 = proxy->width;
   context->y2 = proxy->height;
   context->userdata = proxy;
   context->setter = &lxg_draw_proxy_set_pixel;
   context->getter = &lxg_draw_proxy_get_pixel;
}

void lxg_canvas_free(LXGCanvas* canvas) {
   free(canvas->data);
   free(canvas);
}
