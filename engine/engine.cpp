//
// Created by redstart on 8/5/23.
//

#include "engine.h"
#include "consts.h"
#include <SDL2/SDL.h>
#include <toml.hpp>

// Macro for creating components
#define CREATE_COMPONENT(ComponentType, ...)                                   \
  case ComponentType: {                                                        \
    ComponentType##Component *component =                                      \
        new ComponentType##Component(__VA_ARGS__);                             \
    components[ComponentType].push_back(component);                            \
    break;                                                                     \
  }


const std::unordered_map<std::string, components_e> componentTypes{
    {"Transform", Transform},
    {"Sprite", Sprite},
    {"PhysicsBody", PhysicsBody}};

Engine::Engine() {
  this->screen = nullptr;

  loadScenes();
  readScene();


  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen,
                              &renderer);
}

void Engine::addComponent(IComponent *component, components_e index) {
  this->components[index].push_back(component);
}

Engine::~Engine() {
  for (auto &entity: entities) { delete entity.second; }
  for (auto &i: components)
    for (auto &component: i) delete component;
}

// todo: error handling
void Engine::loadScenes() {
  auto data = toml::parse(resources + "main.toml");
  const auto &scenesArray = data["scenes"].as_array();
  for (const auto &scene: scenesArray) { scenes.push_back(scene.as_string()); }
}

void Engine::readScene(int index) {
  std::string path = resources + scenes[index];
  auto data = toml::parse(path + "/" + "scene.toml");
  const auto &entitiesArray = data["entities"].as_array();
  for (const auto &entity: entitiesArray) {
    std::string entity_name = entity.as_string();
    std::string entity_path = path;
    entity_path.append("/").append(entity_name);
    parseEntity(entity_path);
  }
}

void Engine::parseEntity(const std::string &name) {
  toml::table data = toml::parse(name).as_table();
  auto entity = new Entity(entities.size());
  entities.insert_or_assign(entity->id, entity);
  for (const auto &[componentTypeStr, componentData]: data) {
    auto it = componentTypes.find(componentTypeStr);
    components_e componentType = it->second;
    switch (componentType) {
      CREATE_COMPONENT(
          Transform,
          position_component_t{toml::find(toml::find(componentData, "position"), "x").as_floating(),
                               toml::find(toml::find(componentData, "position"), "y").as_floating()},
          velocity_component_t{toml::find(toml::find(componentData, "velocity"), "x").as_floating(),
                               toml::find(toml::find(componentData, "velocity"), "y").as_floating()},
          entity->id)
      CREATE_COMPONENT(Sprite,
                       position_component_t{toml::find(toml::find(componentData, "position"), "x").as_floating(),
                                            toml::find(toml::find(componentData, "position"), "y").as_floating()},
                       size_component_t{toml::find(toml::find(componentData, "size"), "width").as_floating(),
                                        toml::find(toml::find(componentData, "size"), "height").as_floating()},
                       entity->id,
                       nullptr// Texture, replace with actual value
      )
      CREATE_COMPONENT(PhysicsBody,
                       rect_t{
                           .position = position_component_t{toml::find(toml::find(componentData, "position"), "x").as_floating(),
                                                toml::find(toml::find(componentData, "position"), "y").as_floating()},
                           .size = size_component_t{toml::find(toml::find(componentData, "size"), "width").as_floating(),
                                            toml::find(toml::find(componentData, "size"), "height").as_floating()}
                       },// Shape, replace with actual value
                       false,  // is_circular, replace with actual value
                       entity->id)
      case COMPONENTS_COUNT: break;
    }
    if (componentType <= COMPONENTS_COUNT)
      entity->components[componentType].push_back(components[componentType].back());
  }
}
