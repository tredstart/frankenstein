//
// Created by redstart on 8/3/23.
//
#include "systems.h"
#include "../engine/engine.h"

/* Create a new system with an update function */
systems_i *systems__new(systems_i *self, void (*update_func)) {
  self = (systems_i*)calloc(1, sizeof(*self));
  self->update = update_func;
  return self;
}

/* remove allocated system from memory */
void systems__drop(systems_i *self){
  if (self){
    free(self);
    self = NULL;
  }
}

void render_system(void *context, float dt) {
  engine_s *engine = (engine_s*) context;
  vector *components = engine->components[SPRITE];
  SDL_Renderer *renderer = engine->renderer;
  for (int i = 0; i < components->count; ++i) {
    sprite_component_t *sprite = (sprite_component_t *) vector__get(components, i);
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
  engine_s *engine = (engine_s*) context;
  vector *components = engine->components[COLLIDER];

}

void collides(collider_component_t *collider1, collider_component_t *collider2) {

}

void create_empty_rectangle(sprite_component_t *component, int entity_id) {
  component->size.width = 100;
  component->size.height = 100;
  component->position.x = 10;
  component->position.y = 10;
  component->entity_id = entity_id;
}
