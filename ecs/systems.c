//
// Created by redstart on 8/3/23.
//
#include "systems.h"
#include "../engine/engine.h"
#include "../core/utils.h"

/* Create a new system with an update function */
systems_i *systems__new(systems_i *self, void(*update_func)) {
  self = calloc(1, sizeof(*self));
  self->update = update_func;
  return self;
}

/* remove allocated system from memory */
void systems__drop(systems_i *self) {
  if (self) {
    delete(self);
  }
}

void render_system(void *context, float dt) {
  engine_s *engine = (engine_s *) context;
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

// todo remove this later
sprite_component_t *create_empty_rectangle(int entity_id) {
  position_component_t pos = {.x = 10, .y = 10};
  size_component_t size = {.width = 100, .height = 100};
  sprite_component_t *component = components__new_sprite(pos, size, entity_id, NULL);
  return component;
}
