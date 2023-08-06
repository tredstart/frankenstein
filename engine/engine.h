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
void systems_update(void *engine);
#endif //FRANKENSTEIN_ENGINE_H
