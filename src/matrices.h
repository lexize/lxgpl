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

typedef enum {
   MAT_COMPONENT_X = 0,
   MAT_COMPONENT_Y = 1,
   MAT_COMPONENT_Z = 2,
   MAT_COMPONENT_W = 3
} MatComponent;

Mat2F mat2f_identity();
Mat3F mat3f_identity();
Mat4F mat4f_identity();

Mat2F mat2f_mul(Mat2F a, Mat2F b);
Mat3F mat3f_mul(Mat3F a, Mat3F b);
Mat4F mat4f_mul(Mat4F a, Mat4F b);

Vec2F mat2f_mul_vec(Vec2F a, Mat2F b);
Vec3F mat3f_mul_vec(Vec3F a, Mat3F b);
Vec4F mat4f_mul_vec(Vec4F a, Mat4F b);

Mat2F mat2f_transpose(Mat2F mat);
Mat3F mat3f_transpose(Mat3F mat);
Mat4F mat4f_transpose(Mat4F mat);

float mat2f_get(Mat2F* mat, MatComponent row, MatComponent column);
float mat3f_get(Mat3F* mat, MatComponent row, MatComponent column);
float mat4f_get(Mat4F* mat, MatComponent row, MatComponent column);

void mat2f_set(Mat2F* mat, float val, MatComponent row, MatComponent column);
void mat3f_set(Mat3F* mat, float val, MatComponent row, MatComponent column);
void mat4f_set(Mat4F* mat, float val, MatComponent row, MatComponent column);

float mat2f_determinant(Mat2F mat);
float mat3f_determinant(Mat3F mat);
float mat4f_determinant(Mat4F mat);

Mat2F mat3f_without_intersect(Mat3F mat, MatComponent row, MatComponent column);
Mat3F mat4f_without_intersect(Mat4F mat, MatComponent row, MatComponent column);

Mat2F mat2f_inverse(Mat2F mat);
Mat3F mat3f_inverse(Mat3F mat);
Mat4F mat4f_inverse(Mat4F mat);

Mat4F mat4f_rotate_x(float degrees);
Mat4F mat4f_rotate_y(float degrees);
Mat4F mat4f_rotate_z(float degrees);

Mat4F mat4f_scale(float x, float y, float z);
Mat4F mat4f_translate(float x, float y, float z);

Mat4F mat4f_look(Vec3F cameraPosition, Vec3F cameraTarget, Vec3F cameraUp);
Mat4F mat4f_perspective(float fovDegrees, float aspectRatio, float near, float far);

#endif
