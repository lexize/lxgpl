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
      vec2f_mul(a.r2, vec2fn(b.r1.y))
   );
   Vec2F r2 = vec2f_add(
      vec2f_mul(a.r1, vec2fn(b.r2.x)), 
      vec2f_mul(a.r2, vec2fn(b.r2.y))
   );
   return mat2f(r1, r2);
};

Mat3F mat3f_mul(Mat3F a, Mat3F b) {
   Vec3F r1 = vec3f_add(vec3f_add(
      vec3f_mul(a.r1, vec3fn(b.r1.x)),
      vec3f_mul(a.r2, vec3fn(b.r1.y))),
      vec3f_mul(a.r3, vec3fn(b.r1.z))
   );

   Vec3F r2 = vec3f_add(vec3f_add(
      vec3f_mul(a.r1, vec3fn(b.r2.x)),
      vec3f_mul(a.r2, vec3fn(b.r2.y))),
      vec3f_mul(a.r3, vec3fn(b.r2.z))
   );

   Vec3F r3 = vec3f_add(vec3f_add(
      vec3f_mul(a.r1, vec3fn(b.r3.x)),
      vec3f_mul(a.r2, vec3fn(b.r3.y))),
      vec3f_mul(a.r3, vec3fn(b.r3.z))
   );

   return mat3f(r1, r2, r3);
}

Mat4F mat4f_mul(Mat4F a, Mat4F b) {
   Vec4F r1 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r1.x)),
         vec4f_mul(a.r2, vec4fn(b.r1.y))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r1.z)),
         vec4f_mul(a.r4, vec4fn(b.r1.w))
      )
   );

   Vec4F r2 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r2.x)),
         vec4f_mul(a.r2, vec4fn(b.r2.y))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r2.z)),
         vec4f_mul(a.r4, vec4fn(b.r2.w))
      )
   );

   Vec4F r3 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r3.x)),
         vec4f_mul(a.r2, vec4fn(b.r3.y))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r3.z)),
         vec4f_mul(a.r4, vec4fn(b.r3.w))
      )
   );

   Vec4F r4 = vec4f_add(
      vec4f_add(
         vec4f_mul(a.r1, vec4fn(b.r4.x)),
         vec4f_mul(a.r2, vec4fn(b.r4.y))
      ),
      vec4f_add(
         vec4f_mul(a.r3, vec4fn(b.r4.z)),
         vec4f_mul(a.r4, vec4fn(b.r4.w))
      )
   );

   return mat4f(r1, r2, r3, r4);
}

Vec2F mat2f_mul_vec(Vec2F a, Mat2F b) {
   return vec2f(
      (a.x * b.r1.x) + (a.y * b.r1.y),
      (a.x * b.r2.x) + (a.y * b.r2.y)
   );
}

Vec3F mat3f_mul_vec(Vec3F a, Mat3F b) {
   return vec3f(
      (a.x * b.r1.x) + (a.y * b.r1.y) + (a.z * b.r1.z),
      (a.x * b.r2.x) + (a.y * b.r2.y) + (a.z * b.r2.z),
      (a.x * b.r3.x) + (a.y * b.r3.y) + (a.z * b.r3.z)
   );
}

Vec4F mat4f_mul_vec(Vec4F a, Mat4F b) {
   return vec4f(
      (a.x * b.r1.x) + (a.y * b.r1.y) + (a.z * b.r1.z) + (a.w * b.r1.w),
      (a.x * b.r2.x) + (a.y * b.r2.y) + (a.z * b.r2.z) + (a.w * b.r2.w),
      (a.x * b.r3.x) + (a.y * b.r3.y) + (a.z * b.r3.z) + (a.w * b.r3.w),
      (a.x * b.r4.x) + (a.y * b.r4.y) + (a.z * b.r4.z) + (a.w * b.r4.w)
   );
}

Mat2F mat2f_transpose(Mat2F mat) {
   return mat2f(
      vec2f(mat.r1.x, mat.r2.x),
      vec2f(mat.r1.y, mat.r2.y)
   );
}

Mat3F mat3f_transpose(Mat3F mat) {
   return mat3f(
      vec3f(mat.r1.x, mat.r2.x, mat.r3.x),
      vec3f(mat.r1.y, mat.r2.y, mat.r3.y),
      vec3f(mat.r1.z, mat.r2.z, mat.r3.z)
   );
}

Mat4F mat4f_transpose(Mat4F mat) {
   return mat4f(
      vec4f(mat.r1.x, mat.r2.x, mat.r3.x, mat.r4.x),
      vec4f(mat.r1.y, mat.r2.y, mat.r3.y, mat.r4.y),
      vec4f(mat.r1.z, mat.r2.z, mat.r3.z, mat.r4.z),
      vec4f(mat.r1.w, mat.r2.w, mat.r3.w, mat.r4.w)
   );
}

float mat2f_get(Mat2F* mat, MatComponent row, MatComponent column) {
   Vec2F* r;
   switch (row) {
      case MAT_COMPONENT_X:
         r = &mat->r1;
         break;
      default:
         r = &mat->r2;
         break;
   }

   switch (column) {
      case MAT_COMPONENT_X:
         return r->x;
      default:
         return r->y;
   }
}

void mat2f_set(Mat2F* mat, float val, MatComponent row, MatComponent column) {
   Vec2F* r;
   switch (row) {
      case MAT_COMPONENT_X:
         r = &mat->r1;
         break;
      default:
         r = &mat->r2;
         break;
   }

   switch (column) {
      case MAT_COMPONENT_X:
         r->x = val;
         break;
      default:
         r->y = val;
         break;
   }
}

float mat3f_get(Mat3F* mat, MatComponent row, MatComponent column) {
   Vec3F* r;
   switch (row) {
      case MAT_COMPONENT_X:
         r = &mat->r1;
         break;
      case MAT_COMPONENT_Y:
         r = &mat->r2;
         break;
      default:
         r = &mat->r3;
         break;
   }

   switch (column) {
      case MAT_COMPONENT_X:
         return r->x;
      case MAT_COMPONENT_Y:
         return r->y;
      default:
         return r->z;
   }
}

void mat3f_set(Mat3F* mat, float val, MatComponent row, MatComponent column) {
   Vec3F* r;
   switch (row) {
      case MAT_COMPONENT_X:
         r = &mat->r1;
         break;
      case MAT_COMPONENT_Y:
         r = &mat->r2;
         break;
      default:
         r = &mat->r3;
         break;
   }

   switch (column) {
      case MAT_COMPONENT_X:
         r->x = val;
         break;
      case MAT_COMPONENT_Y:
         r->y = val;
         break;
      default:
         r->z = val;
         break;
   }
}

float mat4f_get(Mat4F* mat, MatComponent row, MatComponent column) {
   Vec4F* r;
   switch (row) {
      case MAT_COMPONENT_X:
         r = &mat->r1;
         break;
      case MAT_COMPONENT_Y:
         r = &mat->r2;
         break;
      case MAT_COMPONENT_Z:
         r = &mat->r3;
         break;
      default:
         r = &mat->r4;
         break;
   }

   switch (column) {
      case MAT_COMPONENT_X:
         return r->x;
      case MAT_COMPONENT_Y:
         return r->y;
      case MAT_COMPONENT_Z:
         return r->z;
      default:
         return r->w;
   }
}

void mat4f_set(Mat4F* mat, float val, MatComponent row, MatComponent column) {
   Vec4F* r;
   switch (row) {
      case MAT_COMPONENT_X:
         r = &mat->r1;
         break;
      case MAT_COMPONENT_Y:
         r = &mat->r2;
         break;
      case MAT_COMPONENT_Z:
         r = &mat->r3;
         break;
      default:
         r = &mat->r4;
         break;
   }

   switch (column) {
      case MAT_COMPONENT_X:
         r->x = val;
         break;
      case MAT_COMPONENT_Y:
         r->y = val;
         break;
      case MAT_COMPONENT_Z:
         r->z = val;
         break;
      default:
         r->w = val;
         break;
   }
}

float mat2f_determinant(Mat2F mat) {
   return (mat.r1.x * mat.r2.y) - (mat.r1.y * mat.r2.x);
}

Mat2F mat2f_inverse(Mat2F mat) {
   float det = 1.f / mat2f_determinant(mat);
   Vec2F r1 = vec2f(mat.r2.y * det, -mat.r1.y * det);
   Vec2F r2 = vec2f(-mat.r2.x * det, mat.r1.x * det);
   return mat2f(r1, r2);
}

float mat3f_determinant(Mat3F mat) {
   Mat2F detAMat = mat3f_without_intersect(mat, MAT_COMPONENT_X, MAT_COMPONENT_X);

   Mat2F detBMat = mat3f_without_intersect(mat, MAT_COMPONENT_X, MAT_COMPONENT_Y);

   Mat2F detCMat = mat3f_without_intersect(mat, MAT_COMPONENT_X, MAT_COMPONENT_Z);

   float detA = mat.r1.x * mat2f_determinant(detAMat);
   float detB = mat.r1.y * mat2f_determinant(detBMat);
   float detC = mat.r1.z * mat2f_determinant(detCMat);

   return detA - detB + detC; 
}

float mat4f_determinant(Mat4F mat) {
   Mat3F detAMat = mat4f_without_intersect(mat, MAT_COMPONENT_X, MAT_COMPONENT_X);
   Mat3F detBMat = mat4f_without_intersect(mat, MAT_COMPONENT_X, MAT_COMPONENT_Y);
   Mat3F detCMat = mat4f_without_intersect(mat, MAT_COMPONENT_X, MAT_COMPONENT_Z);
   Mat3F detDMat = mat4f_without_intersect(mat, MAT_COMPONENT_X, MAT_COMPONENT_W);

   float detA = mat.r1.x * mat3f_determinant(detAMat);
   float detB = mat.r1.y * mat3f_determinant(detBMat);
   float detC = mat.r1.z * mat3f_determinant(detCMat);
   float detD = mat.r1.w * mat3f_determinant(detDMat);

   return detA - detB + detC - detD;
}

Mat2F mat3f_without_intersect(Mat3F mat, MatComponent row, MatComponent column) {
   Vec3F a;
   Vec3F b;
   switch (row) {
      case MAT_COMPONENT_X:
         a = mat.r2;
         b = mat.r3;
         break;
      case MAT_COMPONENT_Y:
         a = mat.r1;
         b = mat.r3;
         break;
      default:
         a = mat.r1;
         b = mat.r2;
         break;
   }
   Vec2F r1;
   Vec2F r2;

   switch (column) {
      case MAT_COMPONENT_X:
         r1 = vec2f(a.y, a.z);
         r2 = vec2f(b.y, b.z);
         break;
      case MAT_COMPONENT_Y:
         r1 = vec2f(a.x, a.z);
         r2 = vec2f(b.x, b.z);
         break;
      default:
         r1 = vec2f(a.x, a.y);
         r2 = vec2f(b.x, b.y);
         break;
   }

   return mat2f(r1, r2);
};


Mat3F mat4f_without_intersect(Mat4F mat, MatComponent row, MatComponent column) {
   Vec4F a;
   Vec4F b;
   Vec4F c;
   switch (row) {
      case MAT_COMPONENT_X:
         a = mat.r2;
         b = mat.r3;
         c = mat.r4;
         break;
      case MAT_COMPONENT_Y:
         a = mat.r1;
         b = mat.r3;
         c = mat.r4;
         break;
      case MAT_COMPONENT_Z:
         a = mat.r1;
         b = mat.r2;
         c = mat.r4;
         break;
      default:
         a = mat.r1;
         b = mat.r2;
         c = mat.r3;
   }
   Vec3F r1;
   Vec3F r2;
   Vec3F r3;

   switch (column) {
      case MAT_COMPONENT_X:
         r1 = vec3f(a.y, a.z, a.w);
         r2 = vec3f(b.y, b.z, b.w);
         r3 = vec3f(c.y, c.z, c.w);
         break;
      case MAT_COMPONENT_Y:
         r1 = vec3f(a.x, a.z, a.w);
         r2 = vec3f(b.x, b.z, b.w);
         r3 = vec3f(c.z, c.z, c.w);
         break;
      case MAT_COMPONENT_Z:
         r1 = vec3f(a.x, a.y, a.w);
         r2 = vec3f(b.x, b.y, b.w);
         r3 = vec3f(c.x, c.y, c.w);
         break;
      default:
         r1 = vec3f(a.x, a.y, a.z);
         r2 = vec3f(b.x, b.y, b.z);
         r3 = vec3f(c.x, c.y, c.z);
         break;
   }

   return mat3f(r1, r2, r3);
};

Mat3F mat3f_inverse(Mat3F mat) {
   Mat3F minors = {0};
   for (int i = 0; i < 9; i++) {
      MatComponent row = i / 3;
      MatComponent column = i % 3;
      Mat2F minor = mat3f_without_intersect(mat, row, column);
      mat3f_set(&minors, mat2f_determinant(minor), row, column);
   }
   Mat3F cofactors = minors;
   for (int i = 0; i < 9; i++) {
      MatComponent row = i / 3;
      MatComponent column = i % 3;
      float mul = row % 2 == 0 ? 1 : -1;
      float val = mat3f_get(&minors, row, column) * mul;
      mat3f_set(&cofactors, val, row, column);
   }
   cofactors = mat3f_transpose(cofactors);
   float mul = 1.f / mat3f_determinant(mat);
   cofactors.r1 = vec3f_mul(cofactors.r1, vec3fn(mul));
   cofactors.r2 = vec3f_mul(cofactors.r2, vec3fn(mul));
   cofactors.r3 = vec3f_mul(cofactors.r3, vec3fn(mul));
   
   return cofactors;
}

Mat4F mat4f_inverse(Mat4F mat) {
   Mat4F minors = {0};
   for (int i = 0; i < 16; i++) {
      MatComponent row = i / 4;
      MatComponent column = i % 4;
      Mat3F minor = mat4f_without_intersect(mat, row, column);
      mat4f_set(&minors, mat3f_determinant(minor), row, column);
   }
   Mat4F cofactors = {0};
   for (int i = 0; i < 16; i++) {
      MatComponent row = i / 4;
      MatComponent column = i % 4;
      float mul = (row % 2 == 0) == (column % 2 == 0) ? 1 : -1;
      float val = mat4f_get(&minors, row, column) * mul;
      mat4f_set(&cofactors, val, row, column);
   }
   cofactors = mat4f_transpose(cofactors);
   float mul = 1.f / mat4f_determinant(mat);
   cofactors.r1 = vec4f_mul(cofactors.r1, vec4fn(mul));
   cofactors.r2 = vec4f_mul(cofactors.r2, vec4fn(mul));
   cofactors.r3 = vec4f_mul(cofactors.r3, vec4fn(mul));
   cofactors.r4 = vec4f_mul(cofactors.r4, vec4fn(mul));
   
   return cofactors;
}
