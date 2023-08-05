//
// Created by redstart on 8/3/23.
//

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

item *item__new(void *value) {
  item *new_item = (item *)malloc(sizeof(item));
  if (!new_item) {
    printf("Error! Cannot create a new map");
    exit(1);
  }
  new_item->next = NULL;
  new_item->prev = NULL;
  new_item->value = value;
  return new_item;
}

vector *vector__new(void *value) {
  vector *new_v = (vector *)malloc(sizeof(vector));
  if (!new_v) {
    printf("Error! Cannot create a new vector");
    exit(1);
  }
  new_v->first = item__new(value);
  new_v->last = new_v->first;
  new_v->count = 1;
  return new_v;
}

item *item__add(item *self, void *value) {
  if (self->next) {
    printf("Error! Not the last item");
    exit(1);
  }
  item *new = item__new(value);
  self->next = new;
  new->prev = self;
  return new;
}

void vector__add(vector *self, void *value) {
  item *new = item__add(self->last, value);
  self->last = new;
  self->count++;
}

void item__drop(item *self) {
  if (self) {
    free(self);
    self = NULL;
  }
}

void vector__drop(vector *self) {
  item *tmp = self->first;
  while (tmp) {
    item *next = tmp->next;
    item__drop(tmp);
    tmp = next;
  }
  self->count = 0;
  self->first = NULL;
  self->last = NULL;
  free(self);
  self = NULL;
}

void *vector__get(vector *self, uint64_t index) {
  if (index >= self->count) {
    printf("Error! Index is out of bounds");
    exit(1);
  }
  item *tmp = self->first;
  for (int i = 0; i < index; ++i) {
    tmp = tmp->next;
  }
  return tmp->value;
}
