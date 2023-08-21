//
// Created by redstart on 8/3/23.
//
#include "systems.h"
void (*SYSTEMS[SYSTEMS_COUNT])(void *engine, float dt) = {
    &render_system,
    &physics_system,
    &movement_system
};

void apply_transform(position_component_t *position, velocity_component_t velocity, float dt);

void render_system(void *context, float dt) {
  auto engine = static_cast<engine_s *>(context);
  vector *components = engine->components[SPRITE];
  SDL_Renderer *renderer = engine->renderer;
  for (int i = 0; i < components->count; ++i) {
    auto sprite = static_cast<sprite_component_t *>(vectorGet(components, i));
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 0, 255 * i, 255, 255);
    rect.h = sprite->size.height;
    rect.w = sprite->size.width;
    rect.x = sprite->position.x;
    rect.y = sprite->position.y;
    SDL_RenderFillRect(renderer, &rect);
  }
}

/* [WIP] */
void physics_system(void *context, float dt) {
  auto engine = static_cast<engine_s *>(context);
  vector *components = engine->components[PHYSICS_BODY];
  for (int i = 0; i < components->count - 1; ++i) {
    for (int j = 1; j < components->count; ++j) {
      auto collider1 = static_cast<physics_body_component_t *>(vectorGet(components, i));
      auto collider2 = static_cast<physics_body_component_t *>(vectorGet(components, j));
      if (collides(&collider1->collider, &collider2->collider)) {
        auto entity = static_cast<entity_t *>(hashMapGet(engine->entities, collider1->entity_id));
        auto transform = static_cast<transform_component_t *>(entity->components[TRANSFORM]->first->value);

        velocity_component_t velocity = {.x = -transform->velocity.x, .y = -transform->velocity.y};

        apply_transform(&transform->position, velocity, dt);

        apply_transform(&collider1->collider.rect.position, velocity, dt);

        vector *sprites = entity->components[SPRITE];
        for (int k = 0; k < sprites->count; ++k) {
          auto sprite = static_cast<sprite_component_t *>(vectorGet(sprites, k));
          apply_transform(&sprite->position, velocity, dt);
        }
      }
    }
  }
}

void movement_system(void *context, float dt) {
  auto engine = static_cast<engine_s *>(context);
  vector *components = engine->components[TRANSFORM];
  for (int i = 0; i < components->count; ++i) {
    auto transform = static_cast<transform_component_t *>(vectorGet(components, i));
    auto entity = static_cast<entity_t *>(hashMapGet(engine->entities, transform->entity_id));
    vector *sprites = entity->components[SPRITE];
    auto physics_body = static_cast<physics_body_component_t *>(entity->components[PHYSICS_BODY]->first->value);
    for (int j = 0; j < sprites->count; ++j) {
      auto sprite = static_cast<sprite_component_t *>(vectorGet(sprites, j));
      apply_transform(&sprite->position, transform->velocity, dt);
    }
    apply_transform(&transform->position, transform->velocity, dt);
    apply_transform(&physics_body->collider.rect.position, transform->velocity, dt);
  }
}

void apply_transform(position_component_t *position, velocity_component_t velocity, float dt) {
  position->x += velocity.x * dt;
  position->y += velocity.y * dt;
}

bool collides(collider_component_t *collider1,
              collider_component_t *collider2) {

  return (
      collider1->rect.position.x < collider2->rect.position.x + collider2->rect.size.width &&
      collider1->rect.position.x + collider1->rect.size.width > collider2->rect.position.x &&
      collider1->rect.position.y < collider2->rect.position.y + collider2->rect.size.height &&
      collider1->rect.position.y + collider1->rect.size.height > collider2->rect.position.y
  );
}


void systems__update(void *engine, float dt) {
  for (auto & update : SYSTEMS)
    (*update)(engine, dt);
}