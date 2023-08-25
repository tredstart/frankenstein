//
// Created by redstart on 8/3/23.
//
#include "systems.h"

void apply_transform(position_component_t *position,
                     velocity_component_t velocity, float dt);

void render_system(Engine *engine, float dt) {
  std::vector<IComponent *> components = engine->components["Sprite"];
  SDL_Renderer *renderer = engine->renderer;
  for (int i = 0; i < components.size(); ++i) {
    auto sprite = dynamic_cast<SpriteComponent *>(components[i]);
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
void physics_system(Engine *engine, float dt) {
  std::vector<IComponent *> components = engine->components["PhysicsBody"];
  for (int i = 0; i < components.size() - 1; ++i) {
    for (int j = 1; j < components.size(); ++j) {
      auto collider1 = dynamic_cast<PhysicsBodyComponent *>(components[i]);
      auto collider2 = dynamic_cast<PhysicsBodyComponent *>(components[j]);
      if (collides(&collider1->collider, &collider2->collider)) {
        Entity *entity = engine->entities.at(collider1->entity_id);
        auto transform = dynamic_cast<TransformComponent *>(
            entity->components["Transform"][0]);

        velocity_component_t velocity = {.x = -transform->velocity.x,
                                         .y = -transform->velocity.y};

        apply_transform(&transform->position, velocity, dt);

        apply_transform(&collider1->collider.rect.position, velocity, dt);

        std::vector<IComponent *> sprites = entity->components["Sprite"];
        for (auto &k: sprites) {
          auto sprite = dynamic_cast<SpriteComponent *>(k);
          apply_transform(&sprite->position, velocity, dt);
        }
      }
    }
  }
}

void movement_system(Engine *engine, float dt) {
  std::vector<IComponent *> components = engine->components["Transform"];
  for (auto &component: components) {
    auto transform = dynamic_cast<TransformComponent *>(component);
    Entity *entity = engine->entities.at(transform->entity_id);
    std::vector<IComponent *> sprites = entity->components["Sprite"];
    auto physics_body = dynamic_cast<PhysicsBodyComponent *>(
        entity->components["PhysicsBody"][0]);
    for (auto &j: sprites) {
      auto sprite = dynamic_cast<SpriteComponent *>(j);
      apply_transform(&sprite->position, transform->velocity, dt);
    }
    apply_transform(&transform->position, transform->velocity, dt);
    apply_transform(&physics_body->collider.rect.position, transform->velocity,
                    dt);
  }
}

void apply_transform(position_component_t *position,
                     velocity_component_t velocity, float dt) {
  position->x += velocity.x * dt;
  position->y += velocity.y * dt;
}

bool collides(collider_component_t *collider1,
              collider_component_t *collider2) {

  return (collider1->rect.position.x <
              collider2->rect.position.x + collider2->rect.size.width &&
          collider1->rect.position.x + collider1->rect.size.width >
              collider2->rect.position.x &&
          collider1->rect.position.y <
              collider2->rect.position.y + collider2->rect.size.height &&
          collider1->rect.position.y + collider1->rect.size.height >
              collider2->rect.position.y);
}


void Systems::update(Engine *engine, float dt) {
  for (auto &update: systems) (*update)(engine, dt);
}
