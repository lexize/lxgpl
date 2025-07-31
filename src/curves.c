#include "curves.h"

Vec2F cubic_bezier_point_vec2f(Vec2F a, Vec2F b, Vec2F c, Vec2F d, float t) {
   Vec2F p1 = vec2f_lerp(a, b, t);
   Vec2F p2 = vec2f_lerp(b, c, t);
   Vec2F p3 = vec2f_lerp(c, d, t);

   Vec2F p4 = vec2f_lerp(p1, p2, t);
   Vec2F p5 = vec2f_lerp(p2, p3, t);

   Vec2F p = vec2f_lerp(p4, p5, t);

   return p;
}

float cubic_bezier_length_vec2f(Vec2F a, Vec2F b, Vec2F c, Vec2F, Vec2F d, int steps) {
   float totalSteps = steps+1;
   bool prevPresent = false;
   Vec2F previous;
   float totalLength = 0.f;
   for (int i = 0; i <= steps; i++) {
      float t = (float)(i+1) / totalSteps;
      Vec2F p1 = prevPresent ? previous : cubic_bezier_point_vec2f(a, b, c, d, (float)(i) / totalSteps);
      Vec2F p2 = cubic_bezier_point_vec2f(a, b, c, d, t);
      totalLength += vec2f_length(vec2f_sub(p1, p2));
   }
   return totalLength;
}
