//
// Created by redstart on 8/3/23.
//

#ifndef FRANKENSTEIN_SYSTEMS_H
#define FRANKENSTEIN_SYSTEMS_H

#include <SDL2/SDL.h>
#include <stddef.h>
#include "consts.h"
#include "../engine/engine.h"

void systems__update(void *engine, float dt);

void render_system(void *context, float dt);
void physics_system(void *context, float dt);
void movement_system(void *context, float dt);

bool collides(collider_component_t *collider1,
              collider_component_t *collider2);


#endif // FRANKENSTEIN_SYSTEMS_H
