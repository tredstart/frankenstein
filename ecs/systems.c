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
  }
}

/* [WIP] */
void physics_system(void *context, float dt) {
  engine_s *engine = context;
  vector *components = engine->components[PHYSICS_BODY];
  for (int i = 0; i < components->count - 1; ++i) {
    for (int j = 1; j < components->count; ++j) {
      physics_body_component_t *collider1 = vector__get(components, i);
      physics_body_component_t *collider2 = vector__get(components, j);
      if (collides(&collider1->collider, &collider2->collider)) {
        // Find entity, get transform. Apply changes to its position and velocity.
        printf("collision found\n");
        entity_t *entity = hash_map__get(engine->entities, collider1->entity_id);
        transform_component_t *transform = entity->components[TRANSFORM]->first->value;

        velocity_component_t velocity = {.x = -transform->velocity.x, .y = -transform->velocity.y};

        apply_transform(&transform->position, velocity, dt);

        // todo: consider making it a rectangle with position
        collider1->collider.rect.x -= transform->velocity.x * dt;
        collider1->collider.rect.y -= transform->velocity.y * dt;

        vector *sprites = entity->components[SPRITE];
        for (int k = 0; k < sprites->count; ++k) {
          sprite_component_t *sprite = vector__get(sprites, k);
          apply_transform(&sprite->position, velocity, dt);
        }
      }
    }
  }
}

void movement_system(void *context, float dt) {
  engine_s *engine = context;
  vector *components = engine->components[TRANSFORM];
  for (int i = 0; i < components->count; ++i) {
    transform_component_t *transform = vector__get(components, i);
    entity_t *entity = hash_map__get(engine->entities, transform->entity_id);
    vector *sprites = entity->components[SPRITE];
    physics_body_component_t *physics_body = entity->components[PHYSICS_BODY]->first->value;
    for (int j = 0; j < sprites->count; ++j) {
      sprite_component_t *sprite = vector__get(sprites, j);
      apply_transform(&sprite->position, transform->velocity, dt);
    }
    apply_transform(&transform->position, transform->velocity, dt);
    physics_body->collider.rect.x += transform->velocity.x * dt;
    physics_body->collider.rect.y += transform->velocity.y * dt;
  }
}

void apply_transform(position_component_t *position, velocity_component_t velocity, float dt) {
  position->x += velocity.x * dt;
  position->y += velocity.y * dt;
}

bool collides(collider_component_t *collider1,
              collider_component_t *collider2) {

  return (
      collider1->rect.x < collider2->rect.x + collider2->rect.w &&
      collider1->rect.x + collider1->rect.w > collider2->rect.x &&
      collider1->rect.y < collider2->rect.y + collider2->rect.h &&
      collider1->rect.y + collider1->rect.h > collider2->rect.y
  );
}


void systems__update(void *engine, float dt) {
  for (int i = 0; i < SYSTEMS_COUNT; ++i)
    (*SYSTEMS[i])(engine, dt);
}