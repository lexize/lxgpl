#include "string_builder.h"
#include "da.h"

size_t sb_append(StringBuilder* sb, const char* str) {
   return sb_append_buf(sb, str, strlen(str));
}

size_t sb_append_buf(StringBuilder* sb, const char* str, size_t len) { 
   size_t c = sb->count + len;
   da_reserve(sb, c);
   
   char* dest = sb->items + sb->count;
   memcpy(dest, str, len);

   return sb->count += len;
}

size_t sb_appendf(StringBuilder* sb, const char* format, ...) {
   va_list args;
   
   va_start(args, format);
   int n = vsnprintf(NULL, 0, format, args);
   va_end(args);

   size_t c = sb->count + n;
   da_reserve(sb, c+1);
   char* dest = sb->items + sb->count;
   va_start(args, format);
   vsnprintf(dest, n+1, format, args);
   va_end(args);

   return sb->count += n;
}
