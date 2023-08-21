//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENGINE_H
#define FRANKENSTEIN_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <vector>
#include <unordered_map>
#include "consts.h"
#include "../ecs/entity.h"

class Engine{
public:
  Engine();
  void addComponent(void *component, components_e index);
  ~Engine() = default;

  SDL_Renderer *renderer{};
  SDL_Window *screen;
  std::vector<void*> components[COMPONENTS_COUNT];
  std::unordered_map<uint64_t, entity_t*> entities;
};
#endif // FRANKENSTEIN_ENGINE_H
