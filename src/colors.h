#include <stdint.h>
#include "math_utils.h"

#ifndef COLORS_H
#define COLORS_H

typedef struct {
   uint8_t a;
   uint8_t r;
   uint8_t g;
   uint8_t b;
} ARGB;

typedef struct {
   uint8_t a;
   uint8_t b;
   uint8_t g;
   uint8_t r;
} ABGR;

typedef struct{
   uint8_t r;
   uint8_t g;
   uint8_t b;
   uint8_t a;
} RGBA;

typedef struct {
   uint8_t b;
   uint8_t g;
   uint8_t r;
   uint8_t a;
} BGRA;

typedef struct {
   uint8_t r;
   uint8_t g;
   uint8_t b;
} RGB;

typedef struct {
   uint8_t b;
   uint8_t g;
   uint8_t r;
} BGR;

typedef struct {
   uint8_t r;
   uint8_t g;
} RG;

ARGB abgr_to_argb(ABGR color);
ARGB rgba_to_argb(RGBA color);
ARGB bgra_to_argb(BGRA color);
ARGB rgb_to_argb(RGB color);
ARGB bgr_to_argb(BGR color);

ABGR argb_to_abgr(ARGB color);
RGBA argb_to_rgba(ARGB color);
BGRA argb_to_bgra(ARGB color);
RGB argb_to_rgb(ARGB color);
BGR argb_to_bgr(ARGB color);

ARGB int_to_argb(int argb);
int argb_to_int(ARGB argb);
ARGB argb_blend(ARGB a, ARGB b);
#endif
