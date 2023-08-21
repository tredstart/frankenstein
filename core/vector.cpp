//
// Created by redstart on 8/3/23.
//
#include "vector.h"
#include "utils.h"

item *itemNew(void *value);

item *itemAdd(item *self, void *value);

void itemDrop(item *self);

void drop_all(vector *self);

/** Create a vector with a new component
 * @example
 * @code
 * sprite_component_t c1;
 * vector *v = vectorNew(&c1);
 * @endcode
 **/
vector *vectorNew(void *value) {
  vector *new_v = static_cast<vector *>(calloc(1, sizeof(*new_v)));
  if (!new_v)
    throw_error("Error! Cannot create a new vector");
  new_v->first = itemNew(value);
  new_v->last = new_v->first;
  new_v->count = 1;
  return new_v;
}

item *itemNew(void *value) {
  item *new_item = static_cast<item *>(calloc(1, sizeof(*new_item)));
  if (!new_item)
    throw_error("Error! Cannot create a new map");
  new_item->next = nullptr;
  new_item->value = value;
  return new_item;
}

/** Add existing component to a vector
 * @example
 * @code
 * sprite_component_t c1;
 * vectorAdd(v, &c1);
 * @endcode
 **/
void vectorAdd(vector *self, void *value) {
  item *new_item = itemAdd(self->last, value);
  self->last = new_item;
  self->count++;
}

item *itemAdd(item *self, void *value) {
  if (self->next)
    throw_error("Error! Not the last item");
  item *new_item = itemNew(value);
  self->next = new_item;
  return new_item;
}

// Clear vector from memory
void vectorDrop(vector *self) {
  if (self) {
    drop_all(self);
    self->count = 0;
    self->first = nullptr;
    self->last = nullptr;
    free(self);
  }
}

void drop_all(vector *self) {
  item *tmp = self->first;
  while (tmp) {
    item *next = tmp->next;
    itemDrop(tmp);
    tmp = next;
  }
}

void itemDrop(item *self) {
  if (self) {
    if (self->value) {
      free(self->value);
    }
    free(self);
  }
}

/** Get item with a component at index
 * @example
 * @code
 * vector *components = engine->components[SPRITE];
 * sprite_component_t *sprite = vectorGet(components, i);
 * @endcode
 * @attention
 * Heavy operation. Consider making a resizable hash table here.
 * https://stackoverflow.com/questions/22437416/best-way-to-resize-a-hash-table
**/
void *vectorGet(vector *self, uint64_t index) {
  if (index >= self->count)
    throw_error("Error! Index is out of bounds");

  item *tmp = self->first;
  for (int i = 0; i < index; ++i) {
    tmp = tmp->next;
  }
  return tmp->value;
}
