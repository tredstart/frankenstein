//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENGINE_H
#define FRANKENSTEIN_ENGINE_H

#include "../ecs/entity.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <unordered_map>
class Engine {
public:
  Engine();
  void addComponent(IComponent *component, components_e index);
  ~Engine();

  SDL_Renderer *renderer{};
  SDL_Window *screen;
  std::vector<IComponent *> components[COMPONENTS_COUNT];
  std::unordered_map<uint64_t, Entity *> entities;
};
#endif// FRANKENSTEIN_ENGINE_H
