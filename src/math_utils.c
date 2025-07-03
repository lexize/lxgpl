#include "math_utils.h"

int int_min(int a, int b) {
   return a < b ? a : b;
}

int int_max(int a, int b) {
   return a > b ? a : b;
}

int ff_mult(int a, uint8_t m) {
   size_t r = a * m / 255;
   return r;
}
