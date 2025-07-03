#ifndef __LXGUI_DRAW_CTX
#define __LXGUI_DRAW_CTX

typedef void (LXGDrawCtxSetter)(void* userdata, int x, int y, int rgba);
typedef int (LXGDrawCtxGetter)(void* userdata, int x, int y);

typedef struct {
   int x1;
   int y1;
   int x2;
   int y2;
   void* userdata;
   LXGDrawCtxSetter* setter;
   LXGDrawCtxGetter* getter;
} LXGDrawCtx;

void lxg_draw_ctx_set_pixel(LXGDrawCtx* ctx, int x, int y, int rgba);

int lxg_draw_ctx_get_pixel(LXGDrawCtx* ctx, int x, int y);

#ifdef  LXGUI_STRIP_PREFIX
#define DrawCtx LXGDrawCtx
#define DrawCtxExecutor LXGDrawCtxExecutor
#define draw_ctx_set_pixel lxg_draw_ctx_set_pixel
#define draw_ctx_get_pixel lxg_draw_ctx_get_pixel
#endif//LXGUI_STRIP_PREFIX

#endif//__LXGUI_DRAW_CTX
