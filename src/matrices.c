#include "matrices.h"

Mat2F mat2f_identity() {
   const Mat2F identity = {
      {1, 0},
      {0, 1}
   };
   return identity;
}

Mat3F mat3f_identity() {
   const Mat3F identity = {
      {1, 0, 0},
      {0, 1, 0},
      {0, 0, 1}
   };
   return identity;
}

Mat4F mat4f_identity() {
   const Mat4F identity = {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
   };
   return identity;
}

Mat2F mat2f(Vec2F r1, Vec2F r2) {
   Mat2F mat = {r1, r2};
   return mat;
}

Mat3F mat3f(Vec3F r1, Vec3F r2, Vec3F r3) {
   Mat3F mat = {r1, r2, r3};
   return mat;
}

Mat4F mat4f(Vec4F r1, Vec4F r2, Vec4F r3, Vec4F r4) {
   Mat4F mat = {r1, r2, r3, r4};
   return mat;
}

Mat2F mat2f_mul(Mat2F a, Mat2F b) {
   Vec2F r1 = vec2f_add(
      vec2f_mul(a.r1, vec2fn(b.r1.x)), 
      vec2f_mul(a.r2, vec2fn(b.r2.x))
   );
   Vec2F r2 = vec2f_add(
      vec2f_mul(a.r1, vec2fn(b.r1.y)), 
      vec2f_mul(a.r2, vec2fn(b.r2.y))
   );
   return mat2f(r1, r2);
};

Mat3F mat3f_mul(Mat3F a, Mat3F b) {
   Vec3F r1 = vec3f_add(vec3f_add(
      vec3f_mul(a.r1, vec3fn(b.r1.x)),
      vec3f_mul(a.r2, vec3fn(b.r2.x))),
      vec3f_mul(a.r3, vec3fn(b.r3.x))
   );

   Vec3F r2 = vec3f_add(vec3f_add(
      vec3f_mul(a.r1, vec3fn(b.r1.y)),
      vec3f_mul(a.r2, vec3fn(b.r2.y))),
      vec3f_mul(a.r3, vec3fn(b.r3.y))
   );

   Vec3F r3 = vec3f_add(vec3f_add(
      vec3f_mul(a.r1, vec3fn(b.r1.z)),
      vec3f_mul(a.r2, vec3fn(b.r2.z))),
      vec3f_mul(a.r3, vec3fn(b.r3.z))
   );

   return mat3f(r1, r2, r3);
}

Mat4F mat4f_mul(Mat4F a, Mat4F b) {
   Vec4F r1 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r1.x)),
         vec4f_mul(a.r2, vec4fn(b.r2.x))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r3.x)),
         vec4f_mul(a.r4, vec4fn(b.r4.x))
      )
   );

   Vec4F r2 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r1.y)),
         vec4f_mul(a.r2, vec4fn(b.r2.y))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r3.y)),
         vec4f_mul(a.r4, vec4fn(b.r4.y))
      )
   );

   Vec4F r3 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r1.z)),
         vec4f_mul(a.r2, vec4fn(b.r2.z))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r3.z)),
         vec4f_mul(a.r4, vec4fn(b.r4.z))
      )
   );

   Vec4F r4 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r1.w)),
         vec4f_mul(a.r2, vec4fn(b.r2.w))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r3.w)),
         vec4f_mul(a.r4, vec4fn(b.r4.w))
      )
   );

   return mat4f(r1, r2, r3, r4);
}

Vec2F mat2f_mul_vec(Vec2F a, Mat2F b) {
   return vec2f(
      (a.x * b.r1.x) + (a.y * b.r2.x),
      (a.x * b.r1.y) + (a.y * b.r1.y)
   );
}

Vec3F mat3f_mul_vec(Vec3F a, Mat3F b) {
   return vec3f(
      (a.x * b.r1.x) + (a.y * b.r2.x) + (a.z * b.r3.x),
      (a.x * b.r1.y) + (a.y * b.r2.y) + (a.z * b.r3.y),
      (a.x * b.r1.z) + (a.y * b.r3.z) + (a.z * b.r3.z)
   );
}

Vec4F mat4f_mul_vec(Vec4F a, Mat4F b) {
   return vec4f(
      (a.x * b.r1.x) + (a.y * b.r2.x) + (a.z * b.r3.x) + (a.w * b.r4.x),
      (a.x * b.r1.y) + (a.y * b.r2.y) + (a.z * b.r3.y) + (a.w * b.r4.y),
      (a.x * b.r1.z) + (a.y * b.r2.z) + (a.z * b.r3.z) + (a.w * b.r4.z),
      (a.x * b.r1.w) + (a.y * b.r2.w) + (a.z * b.r3.w) + (a.w * b.r4.w)
   );
}
