//
// Created by redstart on 8/3/23.
//

#ifndef C_ENGINE_SYSTEMS_H
#define C_ENGINE_SYSTEMS_H

#include "components.h"
#include "../core/vector.h"
#include <SDL2/SDL.h>
#include <stddef.h>
void render_system(vector *components, SDL_Renderer *renderer);
void create_empty_rectangle(sprite_component_t *component, int entity_id);
#endif // C_ENGINE_SYSTEMS_H
