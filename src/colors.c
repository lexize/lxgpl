#include "colors.h"

ARGB int_to_argb(int argb) {
   return *(ARGB*)(&argb);
}

int argb_to_int(ARGB argb) {
   return *(int*)(&argb);
}

ARGB argb_blend(ARGB a, ARGB b) {
   if (b.a == 0) return a;
   ARGB output = a;
   if (a.a < 0xFF && a.a != 0) {
      int diff = 0xFF - a.a;
      uint8_t mul = int_min(diff, b.a);
      output.r = int_min(255, output.r + ff_mult(b.r, mul));
      output.g = int_min(255, output.g + ff_mult(b.g, mul));
      output.b = int_min(255, output.b + ff_mult(b.b, mul));
      if (b.a < diff) {
         output.a += b.a;
         return output;
      }
      else {
         output.a = 255;
         b.a -= diff;
      }
   }
   output.r = int_min(255, ff_mult(b.r, b.a) + ff_mult(output.r, 0xFF-b.a));
   output.g = int_min(255, ff_mult(b.g, b.a) + ff_mult(output.g, 0xFF-b.a));
   output.b = int_min(255, ff_mult(b.b, b.a) + ff_mult(output.b, 0xFF-b.a));
   output.a = 255;
   return output;
}

ARGB abgr_to_argb(ABGR color) {
   ARGB out = {
      .a = color.a,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}

ARGB rgba_to_argb(RGBA color) {
   ARGB out = {
      .a = color.a,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}

ARGB bgra_to_argb(BGRA color) {
   ARGB out = {
      .a = color.a,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}

ARGB rgb_to_argb(RGB color) {
   ARGB out = {
      .a = 0xFF,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}

ARGB bgr_to_argb(BGR color) {
   ARGB out = {
      .a = 0xFF,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}

ABGR argb_to_abgr(ARGB color) {
   ABGR out = {
      .a = color.a,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}

RGBA argb_to_rgba(ARGB color) {
   RGBA out = {
      .a = color.a,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}


BGRA argb_to_bgra(ARGB color) {
   BGRA out = {
      .a = color.a,
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}


RGB argb_to_rgb(ARGB color) {
   RGB out = {
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}

BGR argb_to_bgr(ARGB color) {
   BGR out = {
      .r = color.r,
      .g = color.g,
      .b = color.b,
   };
   return out;
}
