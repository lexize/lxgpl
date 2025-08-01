#include "vectors.h"

#ifndef MATRICES_H
#define MATRICES_H

typedef struct {
   Vec2F r1;
   Vec2F r2;
} Mat2F;

typedef struct {
   Vec3F r1;
   Vec3F r2;
   Vec3F r3;
} Mat3F;

typedef struct {
   Vec4F r1;
   Vec4F r2;
   Vec4F r3;
   Vec4F r4;
} Mat4F;

Mat2F mat2f_identity();
Mat3F mat3f_identity();
Mat4F mat4f_identity();

Mat2F mat2f_mul(Mat2F a, Mat2F b);
Mat3F mat3f_mul(Mat3F a, Mat3F b);
Mat4F mat4f_mul(Mat4F a, Mat4F b);

Vec2F mat2f_mul_vec(Vec2F a, Mat2F b);
Vec3F mat3f_mul_vec(Vec3F a, Mat3F b);
Vec4F mat4f_mul_vec(Vec4F a, Mat4F b);

#endif
