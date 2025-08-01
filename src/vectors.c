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

Vec3I vec3i(int x, int y, int z) {
   Vec3I vec = {x, y, z};
   return vec;
}

Vec3L vec3l(long x, long y, long z) {
   Vec3L vec = {x, y, z};
   return vec;
}

Vec3F vec3f(float x, float y, float z) {
   Vec3F vec = {x, y, z};
   return vec;
}

Vec3D vec3d(double x, double y, double z) {
   Vec3D vec = {x, y, z};
   return vec;
}

Vec4I vec4i(int x, int y, int z, int w) {
   Vec4I vec = {x, y, z, w};
   return vec;
}

Vec4L vec4l(long x, long y, long z, long w) {
   Vec4L vec = {x, y, z, w};
   return vec;
}

Vec4F vec4f(float x, float y, float z, float w) {
   Vec4F vec = {x, y, z, w};
   return vec;
}

Vec4D vec4d(double x, double y, double z, double w) {
   Vec4D vec = {x, y, z, w};
   return vec;
}

Vec2I vec2in(int x) {return vec2i(x, x);}
Vec2L vec2ln(long x) {return vec2l(x, x);}
Vec2F vec2fn(float x) {return vec2f(x, x);}
Vec2D vec2dn(double x) {return vec2d(x, x);}

Vec3I vec3in(int x) {return vec3i(x, x, x);}
Vec3L vec3ln(long x) {return vec3l(x, x, x);}
Vec3F vec3fn(float x) {return vec3f(x, x, x);}
Vec3D vec3dn(double x) {return vec3d(x, x, x);}

Vec4I vec4in(int x) {return vec4i(x, x, x, x);}
Vec4L vec4ln(long x) {return vec4l(x, x, x, x);}
Vec4F vec4fn(float x) {return vec4f(x, x, x, x);}
Vec4D vec4dn(double x) {return vec4d(x, x, x, x);}

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

Vec2I vec2i_lerp(Vec2I a, Vec2I b, uint16_t t) {
   const Vec2I div = {65535, 65535};
   Vec2I mul = {t, t};
   Vec2I diff = vec2i_sub(b, a);
   return vec2i_add(a, vec2i_div(vec2i_mul(diff, mul), div));
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

Vec2L vec2l_lerp(Vec2L a, Vec2L b, uint16_t t) {
   const Vec2L div = {65535, 65535};
   Vec2L mul = {t, t};
   Vec2L diff = vec2l_sub(b, a);
   return vec2l_add(a, vec2l_div(vec2l_mul(diff, mul), div));
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

Vec2F vec2f_lerp(Vec2F a, Vec2F b, float t) {
   Vec2F mul = {t, t};
   Vec2F dif = vec2f_sub(b, a);
   return vec2f_add(a, vec2f_mul(dif, mul));
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

Vec2D vec2d_lerp(Vec2D a, Vec2D b, double t) {
   Vec2D mul = {t, t};
   Vec2D dif = vec2d_sub(b, a);
   return vec2d_add(a, vec2d_mul(dif, mul));
}

Vec3I vec3i_add(Vec3I a, Vec3I b) {
   return vec3i(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3I vec3i_sub(Vec3I a, Vec3I b) {
   return vec3i(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3I vec3i_mul(Vec3I a, Vec3I b) {
   return vec3i(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3I vec3i_div(Vec3I a, Vec3I b) {
   return vec3i(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec3I vec3i_lerp(Vec3I a, Vec3I b, uint16_t t) {
   const Vec3I div = {65535, 65535, 65535};
   Vec3I mul = {t, t, t};
   Vec3I diff = vec3i_sub(b, a);
   return vec3i_add(a, vec3i_div(vec3i_mul(diff, mul), div));
}

Vec3L vec3l_add(Vec3L a, Vec3L b) {
   return vec3l(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3L vec3l_sub(Vec3L a, Vec3L b) {
   return vec3l(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3L vec3l_mul(Vec3L a, Vec3L b) {
   return vec3l(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3L vec3l_div(Vec3L a, Vec3L b) {
   return vec3l(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec3L vec3l_lerp(Vec3L a, Vec3L b, uint16_t t) {
   const Vec3L div = {65535, 65535, 65535};
   Vec3L mul = {t, t, t};
   Vec3L diff = vec3l_sub(b, a);
   return vec3l_add(a, vec3l_div(vec3l_mul(diff, mul), div));
}

Vec3F vec3f_add(Vec3F a, Vec3F b) {
   return vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3F vec3f_sub(Vec3F a, Vec3F b) {
   return vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3F vec3f_mul(Vec3F a, Vec3F b) {
   return vec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3F vec3f_div(Vec3F a, Vec3F b) {
   return vec3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec3F vec3f_lerp(Vec3F a, Vec3F b, float t) {
   Vec3F mul = {t, t, t};
   Vec3F dif = vec3f_sub(b, a);
   return vec3f_add(a, vec3f_mul(dif, mul));
}

Vec3D vec3d_add(Vec3D a, Vec3D b) {
   return vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3D vec3d_sub(Vec3D a, Vec3D b) {
   return vec3d(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3D vec3d_mul(Vec3D a, Vec3D b) {
   return vec3d(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3D vec3d_div(Vec3D a, Vec3D b) {
   return vec3d(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec3D vec3d_lerp(Vec3D a, Vec3D b, double t) {
   Vec3D mul = {t, t, t};
   Vec3D dif = vec3d_sub(b, a);
   return vec3d_add(a, vec3d_mul(dif, mul));
}

Vec4I vec4i_add(Vec4I a, Vec4I b) {
   return vec4i(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vec4I vec4i_sub(Vec4I a, Vec4I b) {
   return vec4i(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vec4I vec4i_mul(Vec4I a, Vec4I b) {
   return vec4i(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vec4I vec4i_div(Vec4I a, Vec4I b) {
   return vec4i(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

Vec4I vec4i_lerp(Vec4I a, Vec4I b, uint16_t t) {
   const Vec4I div = {65535, 65535, 65535, 65535};
   Vec4I mul = {t, t, t, t};
   Vec4I diff = vec4i_sub(b, a);
   return vec4i_add(a, vec4i_div(vec4i_mul(diff, mul), div));
}

Vec4L vec4l_add(Vec4L a, Vec4L b) {
   return vec4l(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vec4L vec4l_sub(Vec4L a, Vec4L b) {
   return vec4l(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vec4L vec4l_mul(Vec4L a, Vec4L b) {
   return vec4l(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vec4L vec4l_div(Vec4L a, Vec4L b) {
   return vec4l(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

Vec4L vec4l_lerp(Vec4L a, Vec4L b, uint16_t t) {
   const Vec4L div = {65535, 65535, 65535, 65535};
   Vec4L mul = {t, t, t, t};
   Vec4L diff = vec4l_sub(b, a);
   return vec4l_add(a, vec4l_div(vec4l_mul(diff, mul), div));
}

Vec4F vec4f_add(Vec4F a, Vec4F b) {
   return vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vec4F vec4f_sub(Vec4F a, Vec4F b) {
   return vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vec4F vec4f_mul(Vec4F a, Vec4F b) {
   return vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vec4F vec4f_div(Vec4F a, Vec4F b) {
   return vec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

Vec4F vec4f_lerp(Vec4F a, Vec4F b, float t) {
   Vec4F mul = {t, t, t, t};
   Vec4F dif = vec4f_sub(b, a);
   return vec4f_add(a, vec4f_mul(dif, mul));
}

Vec4D vec4d_add(Vec4D a, Vec4D b) {
   return vec4d(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vec4D vec4d_sub(Vec4D a, Vec4D b) {
   return vec4d(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vec4D vec4d_mul(Vec4D a, Vec4D b) {
   return vec4d(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vec4D vec4d_div(Vec4D a, Vec4D b) {
   return vec4d(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

Vec4D vec4d_lerp(Vec4D a, Vec4D b, double t) {
   Vec4D mul = {t, t, t, t};
   Vec4D dif = vec4d_sub(b, a);
   return vec4d_add(a, vec4d_mul(dif, mul));
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

float vec2f_length(Vec2F a) {
   return sqrtf(powf(a.x, 2.f) + powf(a.y, 2.f));
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

double vec2d_length(Vec2D a) {
   return sqrt(pow(a.x, 2.) + pow(a.y, 2.));
}

bool vec2d_eq(Vec2D a, Vec2D b) {
   return vec2_eq(a, b);
}
