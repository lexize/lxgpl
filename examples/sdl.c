#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_events.h>
#include <lxgui.h>
#include <assert.h>
#include <stdbool.h>
int main(int argc, char *argv[])
{
   SDL_Init(SDL_INIT_VIDEO);
   SDL_Window* window = SDL_CreateWindow("Test Window", 800, 600, 0);

   SDL_Event event;
   bool exit = false;
   float mouseX, mouseY;
   while (!exit) {
      while(SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_EVENT_QUIT:
               exit = true;
               break;
            case SDL_EVENT_MOUSE_MOTION:
               mouseX = event.motion.x;
               mouseY = event.motion.y;
            default:
               break;
         }
      }
      SDL_Surface* surface = SDL_GetWindowSurface(window);
      SDL_ClearSurface(surface, 1, 1, 1, 1);
      LXGCanvas canvas = {
         .data = surface->pixels,
         .width = surface->w,
         .height = surface->h,
         .mode = LXG_CANVAS_ARGB
      };
      LXGDrawCtx ctx;
      lxg_canvas_setup_context(&canvas, &ctx);
      lxg_draw_circle(&ctx, (int) mouseX, (int) mouseY, 25, 0xFFFFAAFF, true);

      SDL_UpdateWindowSurface(window);
   }

   SDL_DestroyWindow(window);

   SDL_Quit();

   return 0;
}
