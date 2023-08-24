//
// Created by redstart on 8/5/23.
//

#include "engine.h"
#include "consts.h"
#include <SDL2/SDL.h>
#include <functional>
#include <toml.hpp>

Engine::Engine() {
  this->screen = nullptr;

  loadScenes();
  readScene();


  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen,
                              &renderer);
}


Engine::~Engine() {
  for (auto &entity: entities) { delete entity.second; }
  for (auto &i: components)
    for (auto &component: i.second) delete component;
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

void insertVectorToMap(
    const std::string &componentTypeStr, IComponent *newComponent,
    std::unordered_map<std::string, std::vector<IComponent *>> &components) {
  components[componentTypeStr].push_back(newComponent);
}

void Engine::parseEntity(const std::string &name) {
  toml::table data = toml::parse(name).as_table();
  auto entity = new Entity(entities.size());
  entities.insert_or_assign(entity->id, entity);
  for (const auto &[componentTypeStr, componentData]: data) {
    auto componentConstructor = COMPONENTS_MAP.find(componentTypeStr);
    IComponent *newComponent =
        componentConstructor->second(componentData.as_table(), entity->id);
    insertVectorToMap(componentTypeStr, newComponent, entity->components);
    insertVectorToMap(componentTypeStr, newComponent, components);
    entities[entity->id] = entity;
  }
}
