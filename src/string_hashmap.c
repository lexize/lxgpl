#include <string.h>
#include "string_hashmap.h"

int string_compare(char* str1, char* str2) {
   return strcmp(str1, str2) == 0;
}

int string_hasher(char* str) {
   int hash = 5381;
   char c;
   while ((c = *(str++))) {
      hash = ((hash << 5) + hash) + c;
   }
   return hash;
}

HashMap* create_string_hashmap() {
   return hashmap_new(string_hasher, string_compare);
}
