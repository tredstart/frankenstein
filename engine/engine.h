//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENGINE_H
#define FRANKENSTEIN_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "../ecs/components.h"
#include "../core/vector.h"
#include "consts.h"

typedef struct engine_s {
  SDL_Window *screen;
  SDL_Renderer *renderer;
  vector *components[COMPONENTS_COUNT];
} engine_s;

engine_s *engine__new();

void engine__add_component(engine_s *self, void *component, components_e index);

void engine__drop(engine_s *engine);

sprite_component_t *create_empty_rectangle(int entity_id);

#endif // FRANKENSTEIN_ENGINE_H
