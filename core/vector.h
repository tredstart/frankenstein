//
// Created by redstart on 8/3/23.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <cstdint>
#include "../core/utils.h"

typedef struct item {
  void *value;
  struct item *next;
} item;

typedef struct {
  struct item *first;
  struct item *last;
  uint64_t count;
} vector;

vector *vectorNew(void *value);

void vectorAdd(vector *self, void *value);

void vectorDrop(vector *self);

void *vectorGet(vector *self, uint64_t index);

#endif // VECTOR_H
