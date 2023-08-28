//
// Created by redstart on 8/3/23.
//
#include "systems.h"
#include "../core/utils.h"
#include "SFML/Graphics/CircleShape.hpp"

void render_debug_system(const PhysicsBodyComponent &physics_body,
                         sf::RenderWindow *window);

void render_system(Context context, [[maybe_unused]] float dt) {
  std::vector<IComponent *> components = context.components["Sprite"];
  for (auto &component: components) {
    auto sprite = dynamic_cast<SpriteComponent *>(component);
    context.window->draw(sprite->sprite);
  }
}


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
      spriteComponent->setPosition(as_vector<sf::Vector2f>(position));
    }
    render_debug_system(*physics_body, context.window);
  }
}


void render_debug_system(const PhysicsBodyComponent &physics_body,
                         sf::RenderWindow *window) {
  sf::Vector2f position;
  position.x = toPixels(physics_body.body->GetPosition().x);
  position.y = toPixels(physics_body.body->GetPosition().y);
  sf::VertexArray collider(sf::Quads);
  for (int i = 0; i < physics_body.shape.m_count; ++i) {
    b2Vec2 vertex = toPixels(physics_body.shape.m_vertices[i]);
    sf::Vector2f translatedVector = sf::Vector2f(vertex.x, vertex.y) + position;
    collider.append(sf::Vertex(translatedVector, sf::Color(0, 150, 150, 128)));
  }
  collider.setPrimitiveType(sf::Quads);
  window->draw(collider);
}

void Systems::update(Context context, float dt) {
  for (auto &update: systems) (*update)(context, dt);
}
