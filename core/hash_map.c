//
// Created by redstart on 8/19/23.
//

#include "hash_map.h"

short hash(uint64_t id) {
  // This function ensures that hashCodes that differ only by
  // constant multiples at each bit position have a bounded
  // number of collisions (approximately 8 at default load factor).
  id ^= (id >> 20) ^ (id >> 12);
  return (short)((id ^ (id >> 7) ^ (id >> 4)) % DEFAULT_BUFFER);
}

hash_map *hash_map__new() {
  hash_map *map = calloc(1, sizeof(*map));
  if (!map)
    throw_error("Error! Cannot create map");
  map->count = 0;
  return map;
}

void hash_map__insert(hash_map *self, uint64_t key, void *value) {
  self->map[hash(key)].value = value;
  self->count++;
}

void *hash_map__get(hash_map *self, uint64_t key) {
  return self->map[hash(key)].value;
}

void hash_map__drop(hash_map *self) {
  delete(self);
}