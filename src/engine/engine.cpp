//
// Created by redstart on 8/5/23.
//

#include "engine.h"
#include "consts.h"
#include "core/utils.h"
#include "toml.hpp"
#include <SDL2/SDL.h>
#include <functional>

void insertVectorToMap(
    const std::string &componentTypeStr, IComponent *newComponent,
    std::unordered_map<std::string, std::vector<IComponent *>> &components);

Engine::Engine(const std::string &resources) {
  this->resources = resources;
  this->screen = nullptr;
  loadScenes();
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen,
                              &renderer);
}

Engine::~Engine() {
  Logger::info("Exiting engine.");
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  for (auto &entity: entities) { delete entity.second; }
  for (auto &i: components)
    for (auto &component: i.second) delete component;
  SDL_Quit();
}

void Engine::loadScenes() {
  auto data = toml::parse(resources + "main.toml");
  const auto &scenesArray = data["scenes"].as_array();
  if (scenesArray.empty()) {
    Logger::error("No scenes. Cannot load project. Exiting now.");
    throw std::runtime_error("Check " + resources + " folder for main.toml");
  }
  for (const auto &scene: scenesArray) { scenes.push_back(scene.as_string()); }
}

void Engine::readScene(int index) {
  std::string path = resources + scenes[index];
  auto data = toml::parse(path + "/blueprint.toml");
  Logger::info("Trying to read " + path);
  if (data.is_uninitialized() || data["entities"].is_uninitialized()) {
    Logger::error("Bad blueprint. Cannot load project. Exiting now.");
    throw std::runtime_error("Check " + path + " folder for blueprint.toml");
  }
  const auto &entitiesArray = data["entities"].as_array();
  if (entitiesArray.empty()) {
    Logger::error("No entities. Cannot load project. Exiting now.");
    throw std::runtime_error("Check " + path + "/blueprint.toml");
  }
  for (const auto &entity: entitiesArray) {
    std::string entity_name = entity.as_string();
    std::string entity_path = path;
    entity_path.append("/").append(entity_name);
    parseEntity(entity_path);
  }
}


void Engine::parseEntity(const std::string &name) {
  Logger::info("Trying to read entity " + name);
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

void insertVectorToMap(
    const std::string &componentTypeStr, IComponent *newComponent,
    std::unordered_map<std::string, std::vector<IComponent *>> &components) {
  components[componentTypeStr].push_back(newComponent);
}
void Engine::run() {
  if (components.empty()) {
    Logger::error("Cannot run the engine. Components are empty.");

    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 100; i++) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    // [WIP] delta time should be passed to update instead of magic number
    systems.update({
                        components,
                        entities,
                        renderer
                    }, 1);
    SDL_RenderPresent(renderer);
    usleep(15000);
  }
}