//
// Created by redstart on 8/3/23.
//

#ifndef FRANKENSTEIN_SYSTEMS_H
#define FRANKENSTEIN_SYSTEMS_H

#include "../core/vector.h"
#include "components.h"
#include <SDL2/SDL.h>
#include <stddef.h>

typedef enum {
  RENDER,
  SYSTEMS_COUNT,
} systems_e;

typedef struct {
  void (*update)(void *, float);
} systems_i;

systems_i *systems__new(systems_i *self, void(*update_func));

void systems__drop(systems_i *self);

void render_system(void *context, float dt);

sprite_component_t *create_empty_rectangle(int entity_id);

#endif // FRANKENSTEIN_SYSTEMS_H
