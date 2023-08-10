//
// Created by redstart on 8/3/23.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdint.h>

typedef struct item {
  void *value;
  struct item *next;
} item;

typedef struct {
  struct item *first;
  struct item *last;
  uint64_t count;
} vector;

vector *vector__new(void *value);

void vector__add(vector *self, void *new);

void vector__drop(vector *self);

void *vector__get(vector *self, uint64_t index);

#endif // VECTOR_H
