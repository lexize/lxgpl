#include <stdbool.h>
#include "drawing_context.h"
#include <stddef.h>

#ifndef  __LXG_GUI
#define  __LXG_GUI

typedef struct { 
   size_t clazz;
   void* inst;
} LXGWidget;

typedef struct {
   char* title;
   void* platform_data;
   LXGWidget* root_widget;
} LXGWindow;

enum LXGWindowAnchor {
   LXG_ANCHOR_NONE = 0,
   LXG_ANCHOR_LEFT = 1,
   LXG_ANCHOR_RIGHT = 2,
   LXG_ANCHOR_UP = 3,
   LXG_ANCHOR_DOWN = 4,
   LXG_ANCHOR_LEFT_UP = 5,
   LXG_ANCHOR_LEFT_DOWN = 6,
   LXG_ANCHOR_RIGHT_UP = 7,
   LXG_ANCHOR_RIGHT_DOWN = 8,
   LXG_ANCHOR_CENTER = 9
};

/* Function for initialization of LXG. Must be called before creating any windows and handling any input. */
void lxg_init();

/* Platform specific function for Window creation. 
 * Default implementation can be replaced if LXG_WINDOW_NEW_CUSTOM_IMPL is defined */
LXGWindow* lxg_window_new(char* title, int width, int height);

/* Platform specific function for closing a window.
 * Default implementation can be replaced if LXG_WINDOW_CLOSE_CUSTOM_IMPL is defines */
void lxg_window_close(LXGWindow* window);

/* Platform specific function for input handling. 
 * Default implementation can be replaced if LXG_INPUT_HANDLE_CUSTOM_IMPL is defined */
void lxg_handle_input();

/* Updates the LXG, sending and receiving all the needed events, redrawing windows if needed, etc. */
void lxg_update();

// Width getter function for LXG widgets
typedef int(LXGWidgetWidthGetter)(void* widget);
// Height getter function for LXG widgets
typedef int(LXGWidgetHeightGetter)(void* widget);
// Function for checking if widgets needs to be redrawn.
typedef bool(LXGWidgetNeedsRedrawing)(void* widget);
// Function for trying to focus on a widget. Returns true if widget is focused
typedef bool(LXGWidgetFocus)(void* widget);
// Function for handling a key press event. Returns true if widget accepted the key
typedef bool(LXGWidgetOnKey)(void* widget, int key, int state, int modifiers);
// Function for handling a char type event. Returns true if widget accepted the char
typedef bool(LXGWidgetOnChar)(void* widget, int scancode, int state, int modifiers);
// Function for handling a mouse click on a widget. Returns true if widget accepted the click
typedef bool(LXGWidgetOnMouseClick)(void* widget, int mouse_button, int state, int x, int y);
// Function for handling a mouse scroll event on a widget. Returns true if widget accepted the scroll.
typedef bool(LXGWidgetOnMouseScroll)(void* widget, int direction, int amount, int x, int y);
// Function for handling a mouse move event.
typedef void(LXGWidgetOnMouseMove)(void* widget, int x, int y);
// Function for telling a widget what is the max boundaries it can have. If this function wasn't called, widget has no size boundaries.
typedef void(LXGWidgetAcceptBounds)(void* widget, int abs_x, int abs_y, int x, int y, int width, int height);
// Function for rendering a widget. Provided draw context is relative to widget coordinates.
typedef void(LXGWidgetRender)(LXGDrawCtx* ctx, void* widget);
// Function for freeing the widget. The `full` argument tells container widgets to also free all it's children.
typedef void(LXGWidgetFree)(void* widget, bool full);

typedef struct {
   LXGWidgetWidthGetter* width;
   LXGWidgetHeightGetter* height;
   LXGWidgetFocus* focus;
   LXGWidgetNeedsRedrawing* needs_redrawing;
   LXGWidgetOnKey* on_key;
   LXGWidgetOnChar* on_char;
   LXGWidgetOnMouseClick* on_mouse_click;
   LXGWidgetOnMouseScroll* on_mouse_scroll;
   LXGWidgetOnMouseMove* on_mouse_move;
   LXGWidgetAcceptBounds* accept_bounds;
   LXGWidgetRender* render;
   LXGWidgetFree* free;
} LXGWidgetClass;

/**
 * Creates an instance of an empty class for a widget, with some default methods */
LXGWidgetClass* lxg_create_empty_widget_class();

/**
 * Registers new widget in LXG system.
 * Returns number class id used for widget. This number must be used for creation of the widget of registered class later.
 */
size_t lxg_register_new_widget(LXGWidgetClass* widget_class);


int lxg_widget_width(LXGWidget* widget);
int lxg_widget_height(LXGWidget* widget);

bool lxg_widget_needs_redrawing(LXGWidget* widget);

bool lxg_widget_focus(LXGWidget* widget);

bool lxg_widget_on_key(LXGWidget* widget, int key, int state, int modifiers);
bool lxg_widget_on_char(LXGWidget* widget, int scancode, int state, int modifiers);
bool lxg_widget_on_mouse_click(LXGWidget* widget, int mouse_button, int state, int x, int y);
bool lxg_widget_on_mouse_scroll(LXGWidget* widget, int direction, int amount, int x, int y);

void lxg_widget_on_mouse_move(LXGWidget* widget, int mouse_x, int mouse_y);

void lxg_widget_accept_boundaries(LXGWidget* widget, int abs_x, int abs_y, int x, int y, int width, int height);

void lxg_widget_render(LXGDrawCtx* ctx, LXGWidget* widget);
void lxg_widget_render_displaced(LXGDrawCtx* ctx, LXGWidget* widget, int displacement_x, int displacement_y);

void lxg_widget_free(LXGWidget* widget, bool full);

#endif//__LXG_GUI
