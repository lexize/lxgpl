#include "da.h"

#ifndef STRING_UTILS_DEF
#define STRING_UTILS_DEF

struct StringSplit {
   char** items;
   size_t count;
   size_t capacity;
};

/**
 * Splits string by using specified delimeter
 * Returns an array of strings.
 * Allocates a buffer by itself. Must be cleaned up by freeing first string, and then array itself.*/
struct StringSplit string_split(const char* str, char delimeter) {
   size_t input_len = strlen(str);
   char* output_str = malloc(input_len * sizeof(char));
   memcpy(output_str, str, input_len+1);
   
   struct StringSplit arr = {0};
   da_append(&arr, output_str);

   for (size_t i = 0; i < input_len; i++) {
      if (str[i] == delimeter) {
         output_str[i] = 0;
         da_append(&arr, output_str + i + 1);
      }
   }

   return arr;
}

#endif
