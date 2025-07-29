#include <stdint.h>
#include <stddef.h>
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

#define vec2_eq(a, b) (a).x == (b).x && (a).y == (b).y

Vec2I vec2i(int x, int y);
Vec2L vec2l(long x, long y);
Vec2F vec2f(float x, float y);
Vec2D vec2d(double x, double y);

Vec2I vec2i_add(Vec2I a, Vec2I b);
Vec2I vec2i_sub(Vec2I a, Vec2I b);
Vec2I vec2i_mul(Vec2I a, Vec2I b);
Vec2I vec2i_div(Vec2I a, Vec2I b);

Vec2L vec2l_add(Vec2L a, Vec2L b);
Vec2L vec2l_sub(Vec2L a, Vec2L b);
Vec2L vec2l_mul(Vec2L a, Vec2L b);
Vec2L vec2l_div(Vec2L a, Vec2L b);

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
bool vec2f_eq(Vec2F a, Vec2F b);

double vec2d_dot_product(Vec2D a, Vec2D b);
Vec2D vec2d_perpendicular(Vec2D vec);
double vec2d_triangle_area(Vec2D a, Vec2D b, Vec2D c);
bool vec2d_eq(Vec2D a, Vec2D b);
#endif
