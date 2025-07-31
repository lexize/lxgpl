#include "curves.h"

Vec2F cubic_bezier_point_vec2f(Vec2F a, Vec2F b, Vec2F c, Vec2F d, float t) {
   Vec2F mul = vec2f(t, t);
   Vec2F p1 = vec2f_add(a, vec2f_mul(vec2f_sub(b, a), mul));
   Vec2F p2 = vec2f_add(b, vec2f_mul(vec2f_sub(c, b), mul));
   Vec2F p3 = vec2f_add(c, vec2f_mul(vec2f_sub(d, c), mul));

   Vec2F p4 = vec2f_add(p1, vec2f_mul(vec2f_sub(p2, p1), mul));
   Vec2F p5 = vec2f_add(p2, vec2f_mul(vec2f_sub(p3, p2), mul));

   Vec2F p = vec2f_add(p4, vec2f_mul(vec2f_sub(p5, p4), mul));

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
