//
// Created by redstart on 8/19/23.
//

#include "hash_map.h"

short hash(uint64_t id) {
  return (short) (id % DEFAULT_BUFFER);
}

hash_map *hashMapNew() {
  hash_map *map = static_cast<hash_map *>(calloc(1, sizeof(*map)));
  if (!map)
    throw_error("Error! Cannot create map");
  return map;
}

void hashMapInsert(hash_map *self, uint64_t key, void *value) {
  self->map[hash(key)].value = value;
}

void *hashMapGet(hash_map *self, uint64_t key) {
  return self->map[hash(key)].value;
}

