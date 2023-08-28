//
// Created by redstart on 8/3/23.
//
#include "systems.h"
#include "../core/utils.h"
#include "SFML/Graphics/CircleShape.hpp"

void render_system(Context context, [[maybe_unused]] float dt) {
  std::vector<IComponent *> components = context.components["Sprite"];
  for (auto & component : components) {
    auto sprite = dynamic_cast<SpriteComponent *>(component);
    context.window->draw(sprite->sprite);
  }
}

//void render_debug_system(Context context, float dt) {
//  std::vector<IComponent *> components = context.components["Sprite"];
//  SDL_Renderer *renderer = context.renderer;
//  for (int i = 0; i < components.size(); ++i) {
//    auto sprite = dynamic_cast<SpriteComponent *>(components[i]);
//    SDL_Rect rect;
//    SDL_SetRenderDrawColor(renderer, 0, 255 * i, 255, 255);
////    rect.h = sprite->size.height;
////    rect.w = sprite->size.width;
////    rect.x = sprite->position.x;
////    rect.y = sprite->position.y;
//    SDL_RenderFillRect(renderer, &rect);
//  }
//}

/* [WIP] */
void physics_system(Context context, float dt) {
  // time step, velocity iterations, position iterations
  context.world->Step(dt, 2, 6);
  for (auto &entity: context.entities) {
    std::vector<IComponent *> sprite_components =
        entity.second->components["Sprite"];
    // let's assume in the beginning that we will have only one physics body per
    // entity
    auto physics_body = dynamic_cast<PhysicsBodyComponent *>(
        entity.second->components["PhysicsBody"].front());
    auto position = physics_body->body->GetPosition();
    for (auto &sprite_component: sprite_components) {
      auto spriteComponent = dynamic_cast<SpriteComponent *>(sprite_component);
      spriteComponent->sprite.setPosition(position.x, position.y);
    }
  }
}


void Systems::update(Context context, float dt) {
  for (auto &update: systems) (*update)(context, dt);
}
