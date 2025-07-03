#include "drawing_context.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef __LXGUI_CANVAS
#define __LXGUI_CANVAS

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

#ifdef  LXGUI_STRIP_PREFIX
#define Canvas LXGCanvas
#define canvas_new lxg_canvas_new
#define canvas_create_context lxg_canvas_create_context
#define canvas_free lxg_canvas_free
#endif//LXGUI_STRIP_PREFIX

#endif//__LXGUI_CANVAS
