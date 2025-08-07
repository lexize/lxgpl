#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
   int x;
   int y;
} Vec2I;

typedef struct {
   long x;
   long y;
} Vec2L;

typedef struct {
   float x;
   float y;
} Vec2F;

typedef struct {
   double x;
   double y;
} Vec2D;

typedef struct {
   int x;
   int y;
   int z;
} Vec3I;

typedef struct {
   long x;
   long y;
   long z;
} Vec3L;

typedef struct {
   float x;
   float y;
   float z;
} Vec3F;

typedef struct {
   double x;
   double y;
   double z;
} Vec3D;

typedef struct {
   int x;
   int y;
   int z;
   int w;
} Vec4I;

typedef struct {
   long x;
   long y;
   long z;
   long w;
} Vec4L;

typedef struct {
   float x;
   float y;
   float z;
   float w;
} Vec4F;

typedef struct {
   double x;
   double y;
   double z;
   double w;
} Vec4D;

#define VEC2I_ZERO vec2i(0, 0)
#define VEC2L_ZERO vec2l(0, 0)
#define VEC2F_ZERO vec2f(0, 0)
#define VEC2D_ZERO vec2d(0, 0)

#define VEC3I_ZERO vec3i(0, 0, 0)
#define VEC3L_ZERO vec3l(0, 0, 0)
#define VEC3F_ZERO vec3f(0, 0, 0)
#define VEC3D_ZERO vec3d(0, 0, 0)

#define VEC4I_ZERO vec4i(0, 0, 0, 0)
#define VEC4L_ZERO vec4l(0, 0, 0, 0)
#define VEC4F_ZERO vec4f(0, 0, 0, 0)
#define VEC4D_ZERO vec4d(0, 0, 0, 0)

#define VEC2I_ONE vec2i(1, 1)
#define VEC2L_ONE vec2l(1, 1)
#define VEC2F_ONE vec2f(1, 1)
#define VEC2D_ONE vec2d(1, 1)

#define VEC3I_ONE vec3i(1, 1, 1)
#define VEC3L_ONE vec3l(1, 1, 1)
#define VEC3F_ONE vec3f(1, 1, 1)
#define VEC3D_ONE vec3d(1, 1, 1)

#define VEC4I_ONE vec4i(1, 1, 1, 1)
#define VEC4L_ONE vec4l(1, 1, 1, 1)
#define VEC4F_ONE vec4f(1, 1, 1, 1)
#define VEC4D_ONE vec4d(1, 1, 1, 1)

#define vec2_eq(a, b) (a).x == (b).x && (a).y == (b).y
#define vec3_eq(a, b) (a).x == (b).x && (a).y == (b).y && (a).z == (b).z
#define vec4_eq(a, b) (a).x == (b).x && (a).y == (b).y && (a).z == (b).z && (a).w == (b).w

Vec2I vec2i(int x, int y);
Vec2L vec2l(long x, long y);
Vec2F vec2f(float x, float y);
Vec2D vec2d(double x, double y);

Vec3I vec3i(int x, int y, int z);
Vec3L vec3l(long x, long y, long z);
Vec3F vec3f(float x, float y, float z);
Vec3D vec3d(double x, double y, double z);

Vec4I vec4i(int x, int y, int z, int w);
Vec4L vec4l(long x, long y, long z, long w);
Vec4F vec4f(float x, float y, float z, float w);
Vec4D vec4d(double x, double y, double z, double w);

Vec2I vec2in(int x);
Vec2L vec2ln(long x);
Vec2F vec2fn(float x);
Vec2D vec2dn(double x);

Vec3I vec3in(int x);
Vec3L vec3ln(long x);
Vec3F vec3fn(float x);
Vec3D vec3dn(double x);

Vec4I vec4in(int x);
Vec4L vec4ln(long x);
Vec4F vec4fn(float x);
Vec4D vec4dn(double x);

Vec2I vec2i_add(Vec2I a, Vec2I b);
Vec2I vec2i_sub(Vec2I a, Vec2I b);
Vec2I vec2i_mul(Vec2I a, Vec2I b);
Vec2I vec2i_div(Vec2I a, Vec2I b);
Vec2I vec2i_lerp(Vec2I a, Vec2I b, uint16_t t);

Vec2L vec2l_add(Vec2L a, Vec2L b);
Vec2L vec2l_sub(Vec2L a, Vec2L b);
Vec2L vec2l_mul(Vec2L a, Vec2L b);
Vec2L vec2l_div(Vec2L a, Vec2L b);
Vec2L vec2l_lerp(Vec2L a, Vec2L b, uint16_t t);

Vec2F vec2f_add(Vec2F a, Vec2F b);
Vec2F vec2f_sub(Vec2F a, Vec2F b);
Vec2F vec2f_mul(Vec2F a, Vec2F b);
Vec2F vec2f_div(Vec2F a, Vec2F b);
Vec2F vec2f_lerp(Vec2F a, Vec2F b, float t);

Vec2D vec2d_add(Vec2D a, Vec2D b);
Vec2D vec2d_sub(Vec2D a, Vec2D b);
Vec2D vec2d_mul(Vec2D a, Vec2D b);
Vec2D vec2d_div(Vec2D a, Vec2D b);
Vec2D vec2d_lerp(Vec2D a, Vec2D b, double t);

Vec3I vec3i_add(Vec3I a, Vec3I b);
Vec3I vec3i_sub(Vec3I a, Vec3I b);
Vec3I vec3i_mul(Vec3I a, Vec3I b);
Vec3I vec3i_div(Vec3I a, Vec3I b);
Vec3I vec3i_lerp(Vec3I a, Vec3I b, uint16_t t);

Vec3L vec3l_add(Vec3L a, Vec3L b);
Vec3L vec3l_sub(Vec3L a, Vec3L b);
Vec3L vec3l_mul(Vec3L a, Vec3L b);
Vec3L vec3l_div(Vec3L a, Vec3L b);
Vec3L vec3l_lerp(Vec3L a, Vec3L b, uint16_t t);

Vec3F vec3f_add(Vec3F a, Vec3F b);
Vec3F vec3f_sub(Vec3F a, Vec3F b);
Vec3F vec3f_mul(Vec3F a, Vec3F b);
Vec3F vec3f_div(Vec3F a, Vec3F b);
Vec3F vec3f_lerp(Vec3F a, Vec3F b, float t);

Vec3D vec3d_add(Vec3D a, Vec3D b);
Vec3D vec3d_sub(Vec3D a, Vec3D b);
Vec3D vec3d_mul(Vec3D a, Vec3D b);
Vec3D vec3d_div(Vec3D a, Vec3D b);
Vec3D vec3d_lerp(Vec3D a, Vec3D b, double t);

Vec4I vec4i_add(Vec4I a, Vec4I b);
Vec4I vec4i_sub(Vec4I a, Vec4I b);
Vec4I vec4i_mul(Vec4I a, Vec4I b);
Vec4I vec4i_div(Vec4I a, Vec4I b);
Vec4I vec4i_lerp(Vec4I a, Vec4I b, uint16_t t);

Vec4L vec4l_add(Vec4L a, Vec4L b);
Vec4L vec4l_sub(Vec4L a, Vec4L b);
Vec4L vec4l_mul(Vec4L a, Vec4L b);
Vec4L vec4l_div(Vec4L a, Vec4L b);
Vec4L vec4l_lerp(Vec4L a, Vec4L b, uint16_t t);

Vec4F vec4f_add(Vec4F a, Vec4F b);
Vec4F vec4f_sub(Vec4F a, Vec4F b);
Vec4F vec4f_mul(Vec4F a, Vec4F b);
Vec4F vec4f_div(Vec4F a, Vec4F b);
Vec4F vec4f_lerp(Vec4F a, Vec4F b, float t);

Vec4D vec4d_add(Vec4D a, Vec4D b);
Vec4D vec4d_sub(Vec4D a, Vec4D b);
Vec4D vec4d_mul(Vec4D a, Vec4D b);
Vec4D vec4d_div(Vec4D a, Vec4D b);
Vec4D vec4d_lerp(Vec4D a, Vec4D b, double t);

int vec2i_dot_product(Vec2I a, Vec2I b);
Vec2I vec2i_perpendicular(Vec2I vec);
int vec2i_triangle_area(Vec2I a, Vec2I b, Vec2I c);
bool vec2i_eq(Vec2I a, Vec2I b);

long vec2l_dot_product(Vec2L a, Vec2L b);
Vec2L vec2l_perpendicular(Vec2L vec);
long vec2l_triangle_area(Vec2L a, Vec2L b, Vec2L c);
bool vec2l_eq(Vec2L a, Vec2L b);

float vec2f_dot_product(Vec2F a, Vec2F b);
Vec2F vec2f_perpendicular(Vec2F vec);
float vec2f_triangle_area(Vec2F a, Vec2F b, Vec2F c);
float vec2f_length(Vec2F a);
bool vec2f_eq(Vec2F a, Vec2F b);

double vec2d_dot_product(Vec2D a, Vec2D b);
Vec2D vec2d_perpendicular(Vec2D vec);
double vec2d_triangle_area(Vec2D a, Vec2D b, Vec2D c);
double vec2d_length(Vec2D a);
bool vec2d_eq(Vec2D a, Vec2D b);

float vec3f_length(Vec3F a);
float vec4f_length(Vec4F a);

float vec3f_dot(Vec3F a, Vec3F b);
float vec4f_dot(Vec4F a, Vec4F b);

Vec2F vec2f_normalize(Vec2F vec);
Vec3F vec3f_normalize(Vec3F vec);
Vec4F vec4f_normalize(Vec4F vec);

Vec3F vec3f_cross(Vec3F a, Vec3F b);

Vec3F vec2f_aug(Vec2F vec, float num);
Vec4F vec3f_aug(Vec3F vec, float num);

Vec2F vec3f_deaug(Vec3F vec);
Vec3F vec4f_deaug(Vec4F vec);
#endif
