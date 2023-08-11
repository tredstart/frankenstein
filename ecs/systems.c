//
// Created by redstart on 8/3/23.
//
#include "systems.h"

void (*SYSTEMS[SYSTEMS_COUNT])(void *engine, float dt) = {
    &render_system,
    &physics_system
};

void render_system(void *context, float dt) {
  engine_s *engine = context;
  vector *components = engine->components[SPRITE];
  SDL_Renderer *renderer = engine->renderer;
  for (int i = 0; i < components->count; ++i) {
    sprite_component_t *sprite = vector__get(components, i);
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 0, 255 * i, 255, 255);
    rect.h = sprite->size.height;
    rect.w = sprite->size.width;
    rect.x = sprite->position.x;
    rect.y = sprite->position.y;
    SDL_RenderFillRect(renderer, &rect);
    sprite->position.x += 10;
    sprite->position.y += 10;
  }
}

/* [WIP] */
void physics_system(void *context, float dt) {
  engine_s *engine = context;
  vector *components = engine->components[PHYSICS_BODY];
  for (int i = 0; i < components->count - 1; ++i) {
    for (int j = 1; j < components->count; ++j) {
      collider_component_t *collider1 = vector__get(components, i);
      collider_component_t *collider2 = vector__get(components, j);
      if (collides(collider1, collider2)) {
        // Find entity, get transform. Apply changes to its position and velocity.
        printf("collision found\n");
      }
    }
  }
}

bool collides(collider_component_t *collider1,
              collider_component_t *collider2) {
  return (collider1->rect.x < collider2->rect.x + collider2->rect.w &&
         collider1->rect.x + collider1->rect.w > collider2->rect.x &&
         collider1->rect.y < collider2->rect.y + collider2->rect.h &&
         collider1->rect.y + collider1->rect.h > collider2->rect.y);
}


void systems__update(void *engine, float dt) {
  for (int i = 0; i < SYSTEMS_COUNT; ++i)
    (*SYSTEMS[i])(engine, dt);
}