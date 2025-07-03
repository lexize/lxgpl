#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gui.h"
#include "canvas.h"
#include "da.h"

typedef struct {
   LXGWindow** items;
   size_t count;
   size_t capacity;
} WindowsVec;

typedef struct {
   LXGWidgetClass** items;
   size_t count;
   size_t capacity;
} ClassesVec;

static WindowsVec* OPENED_WINDOWS;
static ClassesVec* REGISTERED_CLASSES;

void lxg_init() {
   OPENED_WINDOWS = malloc(sizeof(WindowsVec));
   REGISTERED_CLASSES = malloc(sizeof(ClassesVec));
}

int empty_widget_int_getter(void* _widget) {
   return 0;
}

bool empty_widget_bool_getter(void* _widget) {
   return false;
}

bool empty_widget_key_acceptor(void* _widget, int _k, int _s, int _m) {
   return false;
}

bool empty_widget_mouse_click_acceptor(void* _widget, int _mb, int _s) {
   return false;
}

bool empty_widget_mouse_scroll_acceptor(void* _widget, int _dir, int _am) {
   return false;
}

void empty_widget_mouse_move_acceptor(void* _widget, int _x, int _y) {}

void empty_widget_accept_bounds_acceptor(void* _widget, int _ax, int _ay, int _x, int _y, int _w, int _h) {}

void empty_widget_render(LXGDrawCtx* _ctx, void* _widget) {}

void empty_widget_free(void* widget, bool _free) {
   free(widget);
}

LXGWidgetClass* lxg_create_empty_widget_class() {
   LXGWidgetClass* clazz = malloc(sizeof(LXGWidgetClass));
   LXGWidgetClass clazz_temp = {
      .width = empty_widget_int_getter,
      .height = empty_widget_int_getter,
      .focus = empty_widget_bool_getter,
      .needs_redrawing = empty_widget_bool_getter,
      .on_key = empty_widget_key_acceptor,
      .on_char = empty_widget_key_acceptor,
      .on_mouse_click = empty_widget_mouse_click_acceptor,
      .on_mouse_scroll = empty_widget_mouse_scroll_acceptor,
      .on_mouse_move = empty_widget_mouse_move_acceptor,
      .accept_bounds = empty_widget_accept_bounds_acceptor,
      .render = empty_widget_render,
      .free = empty_widget_free
   };
   *clazz = clazz_temp;
   return clazz;
}

size_t lxg_register_new_widget(LXGWidgetClass* widget_class) {
   size_t current_class_id = REGISTERED_CLASSES->count;
   da_append(REGISTERED_CLASSES, widget_class);
   return current_class_id;
}

LXGWidgetClass* get_widget_class(LXGWidget* widget) {
   return REGISTERED_CLASSES->items[widget->clazz];
}

int lxg_widget_width(LXGWidget* widget) {
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->width(widget->inst);
}

int lxg_widget_height(LXGWidget* widget) {
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->height(widget->inst);
}

bool lxg_widget_needs_redrawing(LXGWidget* widget) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->needs_redrawing(widget->inst);
}

bool lxg_widget_focus(LXGWidget* widget) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->focus(widget->inst);
}

bool lxg_widget_on_key(LXGWidget* widget, int key, int state, int modifiers) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->on_key(widget->inst, key, state, modifiers);
}

bool lxg_widget_on_char(LXGWidget* widget, int scancode, int state, int modifiers) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->on_char(widget->inst, scancode, state, modifiers);
}

bool lxg_widget_on_mouse_click(LXGWidget* widget, int mouse_button, int state, int x, int y) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->on_mouse_click(widget->inst, mouse_button, state, x, y);
}

bool lxg_widget_on_mouse_scroll(LXGWidget* widget, int direction, int amount, int x, int y) {
   LXGWidgetClass* clazz = get_widget_class(widget);
   return clazz->on_mouse_scroll(widget->inst, direction, amount, x, y);
}

void lxg_widget_on_mouse_move(LXGWidget* widget, int mouse_x, int mouse_y) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   clazz->on_mouse_move(widget->inst, mouse_x, mouse_y);
}

void lxg_widget_accept_boundaries(LXGWidget* widget, int abs_x, int abs_y, int x, int y, int width, int height) {
   LXGWidgetClass* clazz = get_widget_class(widget);
   clazz->accept_bounds(widget->inst, abs_x, abs_y, x, y, width, height);
}

void lxg_widget_render(LXGDrawCtx* ctx, LXGWidget* widget) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   clazz->render(ctx, widget->inst);
}

void lxg_widget_render_displaced(LXGDrawCtx* ctx, LXGWidget* widget, int displacement_x, int displacement_y) {
   LXGDrawProxy proxy = {
      .x = displacement_x,
      .y = displacement_y,
      .width = ctx->x2 - ctx->x1,
      .height = ctx->y2 - ctx->y1,
      .destination = ctx
   };
   LXGDrawCtx proxy_ctx = {0};
   lxg_draw_proxy_setup_context(&proxy, &proxy_ctx);
   lxg_widget_render(&proxy_ctx, widget);
}

void lxg_widget_free(LXGWidget* widget, bool full) { 
   LXGWidgetClass* clazz = get_widget_class(widget);
   clazz->free(widget->inst, full);
   free(widget);
}
