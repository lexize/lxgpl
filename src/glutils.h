#ifndef GLUTILS_H
#define GLUTILS_H

#if defined(__linux)
#include <EGL/egl.h>
#elif defined(__WIN32)
#error TODO
#else
#error Unsupported platform.
#endif

typedef struct {
   int glMajor;
   int glMinor;
#if defined(__linux)
   EGLDisplay display;
   EGLContext ctx;
   EGLConfig cfg;
   EGLSurface dummySurface;
#elif defined(__WIN32)

#endif
} LXGGlContext;

LXGGlContext* lxg_gl_context_new();

void lxg_gl_context_free(LXGGlContext* ctx);

#endif
