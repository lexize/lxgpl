#include "drawing_context.h"
#include <stdbool.h>

#ifndef __LXGUI_SHAPES
#define __LXGUI_SHAPES

void lxg_draw_circle(LXGDrawCtx* ctx, int x, int y, int radius, int abgr, bool fill);
void lxg_draw_circle_quart(LXGDrawCtx* ctx, int x, int y, int radius, int rot, int abgr, bool fill);

#define LXGUI_CIRCLE_QUART_RIGHT_UP 0
#define LXGUI_CIRCLE_QUART_RIGHT_DOWN 1
#define LXGUI_CIRCLE_QUART_LEFT_UP 2
#define LXGUI_CIRCLE_QUART_LEFT_DOWN 3

void lxg_draw_rectangle(LXGDrawCtx* ctx, int x1, int y1, int x2, int y2, int abgr);

void lxg_draw_line(LXGDrawCtx* ctx, int x1, int y1, int x2, int y2, int abgr);

#ifdef  LXGUI_STRIP_PREFIX

#define draw_circle lxg_draw_circle
#define draw_circle_outline lxg_draw_circle_outline
#define draw_circle_quart lxg_draw_circle_quart
#define draw_circle_quart_outline lxg_draw_circle_quart_outline

#define draw_rectangle lxg_draw_rectangle

#define draw_line lxg_draw_line

#define CIRCLE_QUART_RIGHT_UP LXGUI_CIRCLE_QUART_RIGHT_UP
#define CIRCLE_QUART_RIGHT_DOWN LXGUI_CIRCLE_QUART_RIGHT_DOWN
#define CIRCLE_QUART_LEFT_UP LXGUI_CIRCLE_QUART_LEFT_UP
#define CIRCLE_QUART_LEFT_DOWN LXGUI_CIRCLE_QUART_LEFT_DOWN
#endif//LXGUI_STRIP_PREFIX

#endif//__LXGUI_SHAPES
