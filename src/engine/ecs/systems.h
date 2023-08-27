//
// Created by redstart on 8/3/23.
//

#ifndef FRANKENSTEIN_SYSTEMS_H
#define FRANKENSTEIN_SYSTEMS_H

#include "box2d/b2_world.h"
#include "entity.h"
#include <SDL2/SDL_render.h>

typedef struct Context {
  std::unordered_map<std::string, std::vector<IComponent *>> &components;
  std::unordered_map<uint64_t, Entity *> &entities;
  SDL_Renderer *renderer;
  b2World *world;
} Context;

void render_system(Context context, float dt);
void physics_system(Context context, float dt);

typedef void(UPDATE_METHOD)(Context engine, float dt);

class Systems {
private:
  std::vector<UPDATE_METHOD *> systems{&render_system, &physics_system};
public:
  Systems() = default;
  ~Systems() = default;
  void update(Context context, float dt);
};


#endif// FRANKENSTEIN_SYSTEMS_H
