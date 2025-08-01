#include "drawing_context.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef __LXG_CANVAS
#define __LXG_CANVAS

typedef enum {
   LXG_CANVAS_ARGB = 0,
   LXG_CANVAS_ABGR = 1,
   LXG_CANVAS_RGBA = 2,
   LXG_CANVAS_BGRA = 3,
   LXG_CANVAS_RGB = 4,
   LXG_CANVAS_BGR = 5,
   LXG_CANVAS_GRAY = 6,
   LXG_CANVAS_GRAY_OPAQUE = 7,
   LXG_CANVAS_GRAY_TRANSPARENT = 8,
   LXG_CANVAS_MONO = 9
} LXGCanvasColorMode;

typedef struct {
   char* data;
   unsigned int width;
   unsigned int height;
   LXGCanvasColorMode mode;
} LXGCanvas;

typedef struct {
   LXGDrawCtx* source;
   LXGDrawCtx* destination;
} LXGStencil;

typedef struct {
   int x;
   int y;
   unsigned int width;
   unsigned int height;
   LXGDrawCtx* destination;
} LXGDrawProxy;


LXGCanvas* lxg_canvas_new(unsigned int width, unsigned int height, LXGCanvasColorMode mode);
LXGDrawCtx* lxg_canvas_create_context(LXGCanvas* canvas);
void lxg_canvas_setup_context(LXGCanvas* canvas, LXGDrawCtx* context);

LXGStencil* lxg_stencil_new(LXGDrawCtx* stencil_source, LXGDrawCtx* destination);
LXGDrawCtx* lxg_stencil_create_context(LXGStencil* stencil);
void lxg_stencil_setup_context(LXGStencil* stencil, LXGDrawCtx* context);


LXGDrawProxy* lxg_draw_proxy_new(int x, int y, unsigned int width, unsigned int height, LXGDrawCtx* destination);
LXGDrawCtx* lxg_draw_proxy_create_context(LXGDrawProxy* canvas);
void lxg_draw_proxy_setup_context(LXGDrawProxy* proxy, LXGDrawCtx* context);

int lxg_canvas_get_pixel(LXGCanvas* canvas, int x, int y);

void lxg_canvas_set_pixel(LXGCanvas* canvas, int x, int y, int color);

void lxg_canvas_free(LXGCanvas* canvas);

#ifdef  LXG_STRIP_PREFIX
#define CANVAS_ARGB             LXG_CANVAS_ARGB,
#define CANVAS_ABGR             LXG_CANVAS_ABGR
#define CANVAS_RGBA             LXG_CANVAS_RGBA
#define CANVAS_BGRA             LXG_CANVAS_BGRA
#define CANVAS_RGB              LXG_CANVAS_RGB
#define CANVAS_BGR              LXG_CANVAS_BGR
#define CANVAS_GRAY             LXG_CANVAS_GRAY
#define CANVAS_GRAY_OPAQUE      LXG_CANVAS_GRAY_OPAQUE
#define CANVAS_GRAY_TRANSPARENT LXG_CANVAS_GRAY_TRANSPARENT
#define CANVAS_MONO             LXG_CANVAS_MONO

#define Canvas LXGCanvas
#define canvas_new lxg_canvas_new
#define canvas_create_context lxg_canvas_create_context
#define canvas_setup_context lxg_canvas_setup_context
#define canvas_free lxg_canvas_free
#define canvas_get_pixel lxg_canvas_get_pixel
#define canvas_set_pixel lxg_canvas_set_pixel

#define Stencil LXGStencil
#define stencil_new lxg_stencil_new
#define stencil_create_context lxg_stencil_create_context

#define DrawProxy LXGDrawProxy
#define draw_proxy_new lxg_draw_proxy_new
#define draw_proxy_create_context
#define draw_proxy_setup_context

#endif//LXG_STRIP_PREFIX

#endif//__LXG_CANVAS
