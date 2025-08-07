#include "glutils.h"
#include "misc.h"

#if defined(__linux)
static EGLint const EGL_ATTRIBUTES[] = {
   EGL_RED_SIZE, 8,
   EGL_GREEN_SIZE, 8,
   EGL_BLUE_SIZE, 8,
   EGL_ALPHA_SIZE, 8,
   EGL_DEPTH_SIZE, 32,
   EGL_NONE
};

static EGLint const DUMMY_PBUFFER_ATTRIBUTES[] = {
   EGL_WIDTH, 1,
   EGL_HEIGHT, 1,
   EGL_NONE
};

LXGGlContext* lxg_gl_context_new() {
   LXGGlContext* ctx = NEW(LXGGlContext);
   ctx->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   eglInitialize(ctx->display, &ctx->glMajor, &ctx->glMinor);
   eglBindAPI(EGL_OPENGL_API);
   eglChooseConfig(ctx->display, EGL_ATTRIBUTES, &ctx->cfg, 1, NULL);
   ctx->ctx = eglCreateContext(ctx->display, ctx->cfg, EGL_NO_CONTEXT, NULL);
   eglMakeCurrent(ctx->display, NULL, NULL, ctx->ctx);
   return ctx;
}

void lxg_gl_context_free(LXGGlContext* ctx) {
   eglDestroyContext(ctx->display, ctx->ctx);
   eglTerminate(ctx->display);
}
#elif defined(__WIN32)
#error TODO
#endif
