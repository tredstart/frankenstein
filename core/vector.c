//
// Created by redstart on 8/3/23.
//
#include "vector.h"
#include "utils.h"
#include <stdlib.h>

item *item__new(void *value);

item *item__add(item *self, void *value);

void item__drop(item *self);

void drop_all(vector *self);

/** Create a vector with a new component
 * @example
 * @code
 * sprite_component_t c1;
 * vector *v = vector__new(&c1);
 * @endcode
 **/
vector *vector__new(void *value) {
  vector *new_v = calloc(1, sizeof(vector));
  if (!new_v)
    throw_error("Error! Cannot create a new vector");
  new_v->first = item__new(value);
  new_v->last = new_v->first;
  new_v->count = 1;
  return new_v;
}

item *item__new(void *value) {
  item *new_item = calloc(1, sizeof(*new_item));
  if (!new_item)
    throw_error("Error! Cannot create a new map");
  new_item->next = NULL;
  new_item->value = value;
  return new_item;
}

/** Add existing component to a vector
 * @example
 * @code
 * sprite_component_t c1;
 * vector__add(v, &c1);
 * @endcode
 **/
void vector__add(vector *self, void *value) {
  item *new = item__add(self->last, value);
  self->last = new;
  self->count++;
}

item *item__add(item *self, void *value) {
  if (self->next)
    throw_error("Error! Not the last item");
  item *new = item__new(value);
  self->next = new;
  return new;
}

// Clear vector from memory
void vector__drop(vector *self) {
  if (self) {
    drop_all(self);
    self->count = 0;
    self->first = NULL;
    self->last = NULL;
    delete(self);
  }
}

void drop_all(vector *self) {
  item *tmp = self->first;
  while (tmp) {
    item *next = tmp->next;
    item__drop(tmp);
    tmp = next;
  }
}

void item__drop(item *self) {
  if (self) {
    if (self->value) {
      delete(self->value);
    }
    delete(self);
  }
}

/** Get item with a component at index
 * @example
 * @code
 * vector *components = engine->components[SPRITE];
 * sprite_component_t *sprite = vector__get(components, i);
 * @endcode
 * @attention
 * Heavy operation. Consider making a resizable hash table here.
 * https://stackoverflow.com/questions/22437416/best-way-to-resize-a-hash-table
**/
void *vector__get(vector *self, uint64_t index) {
  if (index >= self->count)
    throw_error("Error! Index is out of bounds");

  item *tmp = self->first;
  for (int i = 0; i < index; ++i) {
    tmp = tmp->next;
  }
  return tmp->value;
}
