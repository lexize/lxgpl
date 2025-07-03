#include <stdlib.h>
#include <stdio.h>

#define TODO(msg) do {\
   fprintf(stderr, "TODO in %s:%d: %s\n", __FILE__, __LINE__, msg);\
   exit(1);\
} while(0)
