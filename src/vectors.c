#include "vectors.h"

Vec2I vec2i(int x, int y) {
   Vec2I vec = {x, y};
   return vec;
}

Vec2L vec2l(long x, long y) {
   Vec2L vec = {x, y};
   return vec;
}

Vec2F vec2f(float x, float y) {
   Vec2F vec = {x, y};
   return vec;
}

Vec2D vec2d(double x, double y) {
   Vec2D vec = {x, y};
   return vec;
}


Vec2I vec2i_add(Vec2I a, Vec2I b) {
   return vec2i(a.x + b.x, a.y + b.y);
}

Vec2I vec2i_sub(Vec2I a, Vec2I b) {
   return vec2i(a.x - b.x, a.y - b.y);
}

Vec2I vec2i_mul(Vec2I a, Vec2I b) {
   return vec2i(a.x * b.x, a.y * b.y);
}

Vec2I vec2i_div(Vec2I a, Vec2I b) {
   return vec2i(a.x / b.x, a.y / b.y);
}

Vec2L vec2l_add(Vec2L a, Vec2L b) {
   return vec2l(a.x + b.x, a.y + b.y);
}

Vec2L vec2l_sub(Vec2L a, Vec2L b) {
   return vec2l(a.x - b.x, a.y - b.y);
}

Vec2L vec2l_mul(Vec2L a, Vec2L b) {
   return vec2l(a.x * b.x, a.y * b.y);
}

Vec2L vec2l_div(Vec2L a, Vec2L b) {
   return vec2l(a.x / b.x, a.y / b.y);
}

Vec2F vec2f_add(Vec2F a, Vec2F b) {
   return vec2f(a.x + b.x, a.y + b.y);
}

Vec2F vec2f_sub(Vec2F a, Vec2F b) {
   return vec2f(a.x - b.x, a.y - b.y);
}

Vec2F vec2f_mul(Vec2F a, Vec2F b) {
   return vec2f(a.x * b.x, a.y * b.y);
}

Vec2F vec2f_div(Vec2F a, Vec2F b) {
   return vec2f(a.x / b.x, a.y / b.y);
}

Vec2D vec2d_add(Vec2D a, Vec2D b) {
   return vec2d(a.x + b.x, a.y + b.y);
}

Vec2D vec2d_sub(Vec2D a, Vec2D b) {
   return vec2d(a.x - b.x, a.y - b.y);
}

Vec2D vec2d_mul(Vec2D a, Vec2D b) {
   return vec2d(a.x * b.x, a.y * b.y);
}

Vec2D vec2d_div(Vec2D a, Vec2D b) {
   return vec2d(a.x / b.x, a.y / b.y);
}

int vec2i_dot_product(Vec2I a, Vec2I b) {
   size_t x = (a.x * (b.x * 65535)) / 65535;
   size_t y = (a.y * (b.y * 65535)) / 65535;
   return x + y;
}

Vec2I vec2i_perpendicular(Vec2I vec) {
   return vec2i(vec.y, -vec.x);
}

int vec2i_triangle_area(Vec2I a, Vec2I b, Vec2I c) {
   Vec2I ac = vec2i_sub(c, a);
   Vec2I ab = vec2i_sub(b, a);
   Vec2I abPerp = vec2i_perpendicular(ab);
   return vec2i_dot_product(ac, abPerp) / 2;
}

bool vec2i_eq(Vec2I a, Vec2I b) {
   return vec2_eq(a, b);
}

long vec2l_dot_product(Vec2L a, Vec2L b) {
   size_t x = (a.x * (b.x * 65535)) / 65535;
   size_t y = (a.y * (b.y * 65535)) / 65535;
   return x + y;
};

Vec2L vec2l_perpendicular(Vec2L vec) {
   return vec2l(vec.y, -vec.x);
}

long vec2l_triangle_area(Vec2L a, Vec2L b, Vec2L c) {
   Vec2L ac = vec2l_sub(c, a);
   Vec2L ab = vec2l_sub(b, a);
   Vec2L abPerp = vec2l_perpendicular(ab);
   return vec2l_dot_product(ac, abPerp) / 2;
}

bool vec2l_eq(Vec2L a, Vec2L b) {
   return vec2_eq(a, b);
}

float vec2f_dot_product(Vec2F a, Vec2F b) {
   return (a.x * b.x) + (a.y * b.y);
};

Vec2F vec2f_perpendicular(Vec2F vec) {
   return vec2f(vec.y, -vec.x);
}

float vec2f_triangle_area(Vec2F a, Vec2F b, Vec2F c) {
   Vec2F ac = vec2f_sub(c, a);
   Vec2F ab = vec2f_sub(b, a);
   Vec2F abPerp = vec2f_perpendicular(ab);
   return vec2f_dot_product(ac, abPerp) / 2;
}

bool vec2f_eq(Vec2F a, Vec2F b) {
   return vec2_eq(a, b);
}

double vec2d_dot_product(Vec2D a, Vec2D b) {
   return (a.x * b.x) + (a.y * b.y);
};

Vec2D vec2d_perpendicular(Vec2D vec) {
   return vec2d(vec.y, -vec.x);
}

double vec2d_triangle_area(Vec2D a, Vec2D b, Vec2D c) {
   Vec2D ac = vec2d_sub(c, a);
   Vec2D ab = vec2d_sub(b, a);
   Vec2D abPerp = vec2d_perpendicular(ab);
   return vec2d_dot_product(ac, abPerp) / 2;
}

bool vec2d_eq(Vec2D a, Vec2D b) {
   return vec2_eq(a, b);
}
