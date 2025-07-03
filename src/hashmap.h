#include <stdlib.h>

#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_INIT_BUCKETS 16
#define HASHMAP_VALUES_PER_BUCKET 10

typedef unsigned int(HashMapHasher)(void*);
typedef int(HashMapComparator)(void*, void*);

struct HashMapNode_s;

struct HashMapNode_s {
   unsigned int hash;
   void* key;
   void* value;
   struct HashMapNode_s* next;
};

typedef struct HashMapNode_s HashMapNode;

struct HashMapNodes_s {
   HashMapNode** items;
   size_t count;
   size_t capacity;
};

typedef struct HashMapNodes_s HashMapNodes;

struct HashMap_s {
   HashMapHasher* hasher;
   HashMapComparator* comparator;
   size_t size;
   size_t capacity;
   HashMapNodes* buckets;
};

typedef struct HashMap_s HashMap;

HashMap* hashmap_new(HashMapHasher* hasher, HashMapComparator* comparator);

int hashmap_get(HashMap* map, void* key, void** value_out);
void hashmap_set(HashMap* map, void* key, void* value);
int hashmap_remove(HashMap* map, void* key, void** value_out);
void hashmap_free(HashMap* map);

struct HashMapIter_s {
   HashMap* map;
   size_t bucket;
   HashMapNode* current_node;
};

typedef struct HashMapIter_s HashMapIter;

HashMapIter hashmap_iter(HashMap* map);

int hashmap_iter_next(HashMapIter* iter, void** key_out, void** value_out);

#endif
