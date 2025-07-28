#include "math_utils.h"

int int_min(int a, int b) {
   return a < b ? a : b;
}

int int_max(int a, int b) {
   return a > b ? a : b;
}

void int_swap_minmax(int* min, int* max) {
   int aTemp = *min;
   int bTemp = *max;
   if (aTemp > bTemp) {
      *min = bTemp;
      *max = aTemp;
   }
}

int ff_mult(int a, uint8_t m) {
   size_t r = a * m / 255;
   return r;
}
