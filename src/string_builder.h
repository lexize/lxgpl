#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

struct StringBuilder_s {
   char* items;
   size_t count;
   size_t capacity;
};

typedef struct StringBuilder_s StringBuilder;

size_t sb_append(StringBuilder* sb, const char* str);
size_t sb_append_buf(StringBuilder* sb, const char* str, size_t len);

size_t sb_appendf(StringBuilder* sb, const char* format, ...);

#endif
