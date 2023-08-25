#include "components.h"
#include "toml/get.hpp"
#include <utility>

const std::unordered_map<std::string,
                         std::function<IComponent*(toml::table, uint64_t)>>
    COMPONENTS_MAP{
        {"Transform",
         [](toml::table config, uint64_t entity_id) {
           return new TransformComponent(std::move(config), entity_id);
         }},
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

  // todo: will be overhauled by incoming changes in physics system
  auto position_table = config.find("position");
  auto size_table = config.find("size");
  collider.rect.position = {find(position_table->second, "x").as_floating(),
                            find(position_table->second, "y").as_floating()};
  collider.rect.size = {find(size_table->second, "width").as_floating(),
                        find(size_table->second, "height").as_floating()};
  this->entity_id = entity_id;
}

TransformComponent::TransformComponent(toml::table config, uint64_t entity_id) {

  auto position_table = config.find("position");
  auto velocity_table = config.find("velocity");
  position = {find(position_table->second, "x").as_floating(),
              find(position_table->second, "y").as_floating()};
  velocity = {find(velocity_table->second, "x").as_floating(),
              find(velocity_table->second, "y").as_floating()};
  this->entity_id = entity_id;
}
