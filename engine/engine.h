//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENGINE_H
#define FRANKENSTEIN_ENGINE_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "../core/vector.h"
#include "../ecs/systems.h"

typedef struct {
  SDL_Window *screen;
  SDL_Renderer *renderer;
  vector *components[COMPONENTS_COUNT];
  systems_i *systems[SYSTEMS_COUNT];
} engine_s;
engine_s *engine__new();
void engine__add_component(engine_s *self, void *component, components_e index);
void engine__add_system(engine_s *self, systems_i *system, systems_e index, void (*update_func));
void engine__drop(engine_s *engine);
void systems_update(void *engine, float dt);
#endif //FRANKENSTEIN_ENGINE_H
