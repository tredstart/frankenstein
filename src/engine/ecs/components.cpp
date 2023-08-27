#include "components.h"
#include "../core/utils.h"
#include "toml/get.hpp"
#include <utility>

const std::unordered_map<std::string,
                         std::function<IComponent*(toml::table, uint64_t)>>
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
  auto position_table = config.find("position");
  auto size_table = config.find("size");
  position = {find(position_table->second, "x").as_floating(),
              find(position_table->second, "y").as_floating()};
  size = {find(size_table->second, "width").as_floating(),
          find(size_table->second, "height").as_floating()};
  this->entity_id = entity_id;
  // [WIP] for early testing purposes
  //  if (!sprite->texture)
  //    throw_error("Error! No texture!");
  texture = nullptr;
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
  shape.SetAsBox(toMeters(width/2), toMeters(height/2));
  fixtureDefinition.shape = &shape;
  this->entity_id = entity_id;
}
void PhysicsBodyComponent::createBodyInWorld(b2World *world) {
  if (fixtureDefinition.density != 0.0f )
    bodyDefinition.type = b2_dynamicBody;
  body = world->CreateBody(&bodyDefinition);
  body->CreateFixture(&fixtureDefinition);
}