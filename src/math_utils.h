#include <stdint.h>
#include <stddef.h>
#include <math.h>
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

typedef struct {
   int x;
   int y;
} Vec2I;

int int_min(int a, int b);
int int_max(int a, int b);
void int_swap_minmax(int* min, int* max);
int ff_mult(int a, uint8_t m);

int vec2i_dot_product(Vec2I a, Vec2I b);
Vec2I vec2i_perpendicular(Vec2I vec);
int vec2i_triangle_area(Vec2I a, Vec2I b, Vec2I c);
bool vec2i_eq(Vec2I a, Vec2I b);
#endif
