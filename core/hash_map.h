//
// Created by redstart on 8/19/23.
//

#ifndef FRANKENSTEIN_HASH_MAP_H
#define FRANKENSTEIN_HASH_MAP_H

#include <stddef.h>
#include "vector.h"

#define DEFAULT_BUFFER 1024

typedef struct node {
  void *value;
} node;

typedef struct hash_map{
  node map[DEFAULT_BUFFER];
  // todo: this count for now doesn't change anything
  ushort count;
} hash_map;

hash_map *hash_map__new();
void hash_map__insert(hash_map *self, uint64_t key, void *value);
void *hash_map__get(hash_map *self, uint64_t key);
void hash_map__drop(hash_map *self);

#endif //FRANKENSTEIN_HASH_MAP_H
