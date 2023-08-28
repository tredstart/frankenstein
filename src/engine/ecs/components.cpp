#include "components.h"
#include "../core/utils.h"
#include "toml/get.hpp"
#include <utility>
#include <SDL2/SDL_image.h>
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
  auto position_table = config["position"];

  // migrate to opengl and see
//  destination.x = static_cast<float >(position_table["x"].as_floating());

  texture_path = config["texture"].as_string();

  this->entity_id = entity_id;

}

void SpriteComponent::createTexture(SDL_Renderer *renderer, const std::string& resources) {
  imageSurface = IMG_Load((resources + texture_path).c_str());
  texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
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