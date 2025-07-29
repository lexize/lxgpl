#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "vectors.h"
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int int_min(int a, int b);
int int_max(int a, int b);
void int_swap_minmax(int* min, int* max);
int ff_mult(int a, uint8_t m);
#endif
