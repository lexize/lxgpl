#include "drawing_context.h"
#include <stdbool.h>
#include <stddef.h>
#include "math_utils.h"
#include "vectors.h"

#ifndef __LXG_SHAPES
#define __LXG_SHAPES

typedef void (LXGTrianglePainterFunc)(void* userdata, int x, int y, uint16_t aPower, uint16_t bPower, uint16_t cPower);

typedef struct {
   LXGTrianglePainterFunc* paint;
   void* userdata;
} LXGTrianglePainter;

void lxg_draw_circle(LXGDrawCtx* ctx, int x, int y, int radius, int abgr, bool fill);
void lxg_draw_circle_quart(LXGDrawCtx* ctx, int x, int y, int radius, int rot, int abgr, bool fill);

#define LXG_CIRCLE_QUART_RIGHT_UP 0
#define LXG_CIRCLE_QUART_RIGHT_DOWN 1
#define LXG_CIRCLE_QUART_LEFT_UP 2
#define LXG_CIRCLE_QUART_LEFT_DOWN 3

void lxg_draw_rectangle(LXGDrawCtx* ctx, int x1, int y1, int x2, int y2, int abgr);

void lxg_draw_line(LXGDrawCtx* ctx, int x1, int y1, int x2, int y2, int abgr);

void lxg_draw_triangle(LXGDrawCtx* ctx, Vec2I a, Vec2I b, Vec2I c, int abgr);

void lxg_draw_triangle_textured(LXGTrianglePainter* ctx, Vec2I a, Vec2I b, Vec2I c);

#ifdef  LXG_STRIP_PREFIX

#define draw_circle lxg_draw_circle
#define draw_circle_quart lxg_draw_circle_quart
#define draw_rectangle lxg_draw_rectangle
#define draw_line lxg_draw_line
#define draw_triangle lxg_draw_triangle
#define draw_triangle_textured

#define TrianglePainter LXGTrianglePainter

#define CIRCLE_QUART_RIGHT_UP LXG_CIRCLE_QUART_RIGHT_UP
#define CIRCLE_QUART_RIGHT_DOWN LXG_CIRCLE_QUART_RIGHT_DOWN
#define CIRCLE_QUART_LEFT_UP LXG_CIRCLE_QUART_LEFT_UP
#define CIRCLE_QUART_LEFT_DOWN LXG_CIRCLE_QUART_LEFT_DOWN
#endif//LXG_STRIP_PREFIX

#endif//__LXG_SHAPES
