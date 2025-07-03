#define DA_INIT_CAPACITY 16

#define da_init(da, cap) do { (da)->items = calloc((cap), sizeof(*((da)->items)));\
   (da)->capacity = (cap); } while (0)

#define da_realloc(da, cap) do { (da)->items = realloc((da)->items, sizeof(*((da)->items))*(cap));\
(da)->capacity = (cap); } while (0)

#define da_reserve(da, cap) do {\
   if ((da)->capacity < (cap)) {\
      int init = (da)->capacity == 0;\
      size_t n_cap = init ? DA_INIT_CAPACITY : (da)->capacity;\
      while (n_cap < (cap)) {\
         n_cap = n_cap * 2;\
      }\
      if (init) da_init((da), n_cap);\
      else da_realloc((da), n_cap);\
   }\
} while (0)

#define da_append(da, item) do {\
   if ((da)->capacity == 0) da_init((da), DA_INIT_CAPACITY);\
   else if ((da)->count >= (da)->capacity) da_realloc((da), (da)->capacity*2*sizeof(*((da)->items)));\
   (da)->items[(da)->count++]=item;\
} while (0)

#define da_remove(da, index) do {\
   for (size_t i = (index); index < (da)->count; index++) {\
      (da)->items[index] = (da)->items[index+1];\
   }\
   (da)->count--;\
} while (0)

#define da_free(da) do {\
   free((da)->items);\
   free(da);\
} while (0)
