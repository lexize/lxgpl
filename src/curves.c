#include "curves.h"

Vec2F cubic_bezier_point_vec2f(Vec2F a, Vec2F b, Vec2F c, Vec2F d, float t) {
   const Mat4F COOFS_MAT = {
      { 1, 0,  0, 0},
      {-3, 3,  0, 0},
      { 3,-6,  3, 0},
      {-1, 3, -3, 1}
   };
   Vec4F tS = {1, t, powf(t, 2), powf(t, 3)};
   Vec4F coofs = mat4f_mul_vec(tS, COOFS_MAT);
   Vec2F p = vec2f_add(
         vec2f_add(vec2f_mul(a, vec2fn(coofs.x)), vec2f_mul(b, vec2fn(coofs.y))),
         vec2f_add(vec2f_mul(c, vec2fn(coofs.z)), vec2f_mul(d, vec2fn(coofs.w)))
   );
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
