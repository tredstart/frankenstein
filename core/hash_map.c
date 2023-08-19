//
// Created by redstart on 8/19/23.
//

#include "hash_map.h"

short hash(uint64_t id) {
  return (short) (id % DEFAULT_BUFFER);
}

hash_map *hash_map__new() {
  hash_map *map = calloc(1, sizeof(*map));
  if (!map)
    throw_error("Error! Cannot create map");
  return map;
}

void hash_map__insert(hash_map *self, uint64_t key, void *value) {
  self->map[hash(key)].value = value;
}

void *hash_map__get(hash_map *self, uint64_t key) {
  return self->map[hash(key)].value;
}

