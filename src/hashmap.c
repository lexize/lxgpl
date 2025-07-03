#include "hashmap.h"
#include "da.h"
#include <stdio.h>

HashMap* hashmap_new(HashMapHasher* hasher, HashMapComparator* comparator) {
   HashMap* map = calloc(1, sizeof(HashMap));
   map->hasher = hasher;
   map->comparator = comparator;
   map->size = 0;
   map->capacity = 0;
   map->buckets = calloc(1, sizeof(HashMapNodes));
   return map;
}

int hashmap_get_hash(HashMap* map, void* key) {
   return map->hasher(key);
}

int hashmap_get(HashMap* map, void* key, void** value_out) {
   if (map->size == 0) return 0;
   
   unsigned int key_hash = hashmap_get_hash(map, key);
   unsigned int item_bucket = key_hash % map->buckets->count;
   
   HashMapNode* node = map->buckets->items[item_bucket];
   while (node) {
      if (node->hash == key_hash && map->comparator(key, node->key)) {
         if (value_out) *value_out = node->value;
         return 1;
      }
      node = node->next;
   }

   return 0;
}

void hashmap_resort(HashMap* map) {
   size_t buckets = map->buckets->count;
   for (size_t bucket = 0; bucket < buckets; bucket++) {
      HashMapNode** prev_node = &map->buckets->items[bucket];
      while (*prev_node) {
         HashMapNode* node = *prev_node;
         HashMapNode* next = node->next;
         unsigned int node_bucket = node->hash % buckets;
         if (node_bucket != bucket) {
            HashMapNode** proper_bucket = &map->buckets->items[node_bucket];
            HashMapNode* proper_bucket_first_node = *proper_bucket; 
            node->next = proper_bucket_first_node;
            *proper_bucket = node;
            *prev_node = next;
         }
         else {
            prev_node = &node->next;
         }
      }
   }
}

void hashmap_resize(HashMap* map) {
   if (map->capacity == 0) {
      da_init(map->buckets, HASHMAP_INIT_BUCKETS);
      map->capacity = (HASHMAP_INIT_BUCKETS * HASHMAP_VALUES_PER_BUCKET * 3) / 4;
      map->buckets->count = map->buckets->capacity;
   }
   else {
      da_realloc(map->buckets, map->buckets->capacity * 2);
      map->capacity = (map->buckets->capacity * HASHMAP_VALUES_PER_BUCKET * 3) / 4;
      map->buckets->count = map->buckets->capacity;
      hashmap_resort(map);
   }
}

void hashmap_set(HashMap* map, void* key, void* value) {
   if (map->capacity == 0) hashmap_resize(map);
   unsigned int key_hash = hashmap_get_hash(map, key);
   unsigned int item_bucket = key_hash % map->buckets->count;
   HashMapNode** prev_node = &map->buckets->items[item_bucket];
   HashMapNode* node = *prev_node;
   while (node) {
      if (node->hash == key_hash && map->comparator(node->key, key)) {
         node->value = value;
         return;
      }
      prev_node = &node->next;
      node = node->next;
   }
   HashMapNode* new_node = calloc(1, sizeof(HashMapNode));
   new_node->hash = key_hash;
   new_node->key = key;
   new_node->value = value;
   *prev_node = new_node;
   map->size++;
   if (map->size >= map->capacity) hashmap_resize(map);
   return;
}

int hashmap_remove(HashMap* map, void* key, void** value_out) {
   if (map->size == 0) return 0;
   
   unsigned int key_hash = hashmap_get_hash(map, key);
   unsigned int item_bucket = key_hash % map->buckets->count;
   
   HashMapNode** prev_node = &map->buckets->items[item_bucket];
   HashMapNode* node = *prev_node;
   while (node) {
      if (node->hash == key_hash && map->comparator(key, node->key)) {
         *prev_node = node->next;
         if (value_out) *value_out = node->value;
         free(node);
         return 1;
      }
      prev_node = &node->next;
      node = *prev_node;
   }

   return 0;
}

void hashmap_free(HashMap* map) {
   for (size_t bucket = 0; bucket < map->buckets->count; bucket++) {
      HashMapNode* node = map->buckets->items[bucket];
      while (node) {
         HashMapNode* next = node->next;
         free(node);
         node = next;
      }
   }
   da_free(map->buckets);
   free(map);
}

HashMapIter hashmap_iter(HashMap* map) {
   HashMapIter iter = {
      .map = map
   };
   for (; iter.bucket < map->buckets->count; iter.bucket++) {
      HashMapNode* node = map->buckets->items[iter.bucket];
      if (node) { iter.current_node = node; break;}
   }
   return iter;
}

int hashmap_iter_next(HashMapIter* iter, void** key_out, void** value_out) {
   if (!iter->current_node) return 0;
   HashMapNode* node = iter->current_node;
   if (key_out) *key_out = node->key;
   if (value_out) *value_out = node->value;
   if (node->next) iter->current_node = node->next;
   else {
      HashMap* map = iter->map;
      for (iter->bucket++; iter->bucket < map->buckets->count; iter->bucket++) {
         node = map->buckets->items[iter->bucket];
         if (node) { iter->current_node = node; return 1;}
      }
      iter->current_node = NULL;
   }
   return 1;
}
