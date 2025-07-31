#include "vectors.h"
#include <math.h>
#include <stdbool.h>
#ifndef CURVES_H
#define CURVES_H

Vec2F cubic_bezier_point_vec2f(Vec2F a, Vec2F b, Vec2F c, Vec2F d, float t);
float cubic_bezier_length_vec2f(Vec2F a, Vec2F b, Vec2F c, Vec2F, Vec2F d, int steps);

#endif
