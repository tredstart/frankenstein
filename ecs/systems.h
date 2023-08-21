//
// Created by redstart on 8/3/23.
//

#ifndef FRANKENSTEIN_SYSTEMS_H
#define FRANKENSTEIN_SYSTEMS_H


#include "../engine/engine.h"
void render_system(Engine *context, float dt);
void physics_system(Engine *context, float dt);
void movement_system(Engine *context, float dt);

typedef void(UPDATE_METHOD)(Engine *engine, float dt);

class Systems {
private:
  std::vector<UPDATE_METHOD *> systems{&render_system, &physics_system,
                                       &movement_system};

public:
  Systems() = default;
  ~Systems() = default;
  void update(Engine *engine, float dt);
};

bool collides(collider_component_t *collider1, collider_component_t *collider2);


#endif// FRANKENSTEIN_SYSTEMS_H
