#include "math_utils.h"

int int_min(int a, int b) {
   return a < b ? a : b;
}

int int_max(int a, int b) {
   return a > b ? a : b;
}

void int_swap_minmax(int* min, int* max) {
   int aTemp = *min;
   int bTemp = *max;
   if (aTemp > bTemp) {
      *min = bTemp;
      *max = aTemp;
   }
}

int ff_mult(int a, uint8_t m) {
   size_t r = a * m / 255;
   return r;
}

int vec2i_dot_product(Vec2I a, Vec2I b) {
   size_t x = (a.x * (b.x * 65535)) / 65535;
   size_t y = (a.y * (b.y * 65535)) / 65535;
   return x + y;
}

Vec2I vec2i_perpendicular(Vec2I vec) {
   Vec2I out = {
      .x = vec.y,
      .y = -vec.x
   };
   return out;
}

int vec2i_triangle_area(Vec2I a, Vec2I b, Vec2I c) {
   Vec2I ac = {
      .x = c.x - a.x,
      .y = c.y - a.y
   };
   Vec2I ab = {
      .x = b.x - a.x,
      .y = b.y - a.y
   };
   Vec2I abPerp = vec2i_perpendicular(ab);
   return vec2i_dot_product(ac, abPerp) / 2;
}
