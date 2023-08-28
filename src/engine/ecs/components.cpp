#include "components.h"
#include "../core/utils.h"
#include "toml/get.hpp"
#include <utility>

inline float getHalfSize(int extent);

const std::unordered_map<std::string,
                         std::function<IComponent *(toml::table, uint64_t)>>
    COMPONENTS_MAP{
        {"Sprite",
         [](toml::table config, uint64_t entity_id) {
           return new SpriteComponent(std::move(config), entity_id);
         }},
        {"PhysicsBody",
         [](toml::table config, uint64_t entity_id) {
           return new PhysicsBodyComponent(std::move(config), entity_id);
         }},
    };

SpriteComponent::SpriteComponent(toml::table config, uint64_t entity_id) {
  Logger::info("Creating SpriteComponent");
  auto position_table = config["position"];

  texture_path = config["texture"].as_string();
  texture.setSmooth(false);
  sprite.setPosition(static_cast<float>(position_table["x"].as_floating()),
                     static_cast<float>(position_table["y"].as_floating()));
  this->entity_id = entity_id;
}

void SpriteComponent::loadTexture(const std::string &resources) {
  texture.loadFromFile(resources + texture_path);
  sprite.setTexture(texture);
}

void SpriteComponent::setPosition(sf::Vector2f new_position) {
  float new_x =
      toPixels(new_position.x) - getHalfSize(sprite.getTextureRect().width);
  float new_y =
      toPixels(new_position.y) - getHalfSize(sprite.getTextureRect().height);
  sf::Vector2f position(new_x, new_y);
  sprite.setPosition(position);
}

inline float getHalfSize(int extent) {
  return static_cast<float>(extent) / 2.0f;
}

PhysicsBodyComponent::PhysicsBodyComponent(toml::table config,
                                           uint64_t entity_id) {
  Logger::info("Creating PhysicsBodyComponents");
  auto position_table = config["position"].as_table();
  auto size_table = config["size"].as_table();
  auto density = static_cast<float>(config["density"].as_floating());
  auto friction = static_cast<float>(config["friction"].as_floating());

  auto x = static_cast<float>(position_table["x"].as_floating());
  auto y = static_cast<float>(position_table["y"].as_floating());

  auto width = static_cast<float>(size_table["width"].as_floating());
  auto height = static_cast<float>(size_table["height"].as_floating());

  fixtureDefinition.density = density;
  fixtureDefinition.friction = friction;
  bodyDefinition.position.Set(toMeters(x), toMeters(y));
  shape.SetAsBox(toMeters(width), toMeters(height));
  fixtureDefinition.shape = &shape;
  this->entity_id = entity_id;
}
void PhysicsBodyComponent::createBodyInWorld(b2World *world) {
  if (fixtureDefinition.density != 0.0f) bodyDefinition.type = b2_dynamicBody;
  body = world->CreateBody(&bodyDefinition);
  body->CreateFixture(&fixtureDefinition);
}