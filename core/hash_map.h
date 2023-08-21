//
// Created by redstart on 8/19/23.
//

#ifndef FRANKENSTEIN_HASH_MAP_H
#define FRANKENSTEIN_HASH_MAP_H

#include <cstddef>
#include "vector.h"

#define DEFAULT_BUFFER 1024

typedef struct node {
  void *value;
} node;

typedef struct hash_map{
  node map[DEFAULT_BUFFER];
} hash_map;

hash_map *hashMapNew();
void hashMapInsert(hash_map *self, uint64_t key, void *value);
void *hashMapGet(hash_map *self, uint64_t key);
void hashMapDrop(hash_map *self);

#endif //FRANKENSTEIN_HASH_MAP_H
