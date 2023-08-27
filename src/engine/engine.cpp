//
// Created by redstart on 8/5/23.
//

#include "engine.h"
#include "consts.h"
#include "core/utils.h"
#include "toml.hpp"
#include <SDL2/SDL.h>
#include <functional>
void parsingError(const std::string &msg, const std::string &path);
void insertVectorToMap(
    const std::string &componentTypeStr, IComponent *newComponent,
    std::unordered_map<std::string, std::vector<IComponent *>> &components);

Engine::Engine(const std::string &resources) {
  this->resources = resources;
  this->screen = nullptr;
  b2Vec2 gravity(0.0f, 10.0f);
  world = new b2World(gravity);
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
  for (auto &componentType: components)
    for (auto &component: componentType.second) delete component;
  delete world;
  SDL_Quit();
}

void Engine::loadScenes() {
  auto data = toml::parse(resources + "main.toml");
  const auto &scenesArray = data["scenes"].as_array();
  if (scenesArray.empty())
    parsingError("No scenes. Cannot load project. Exiting now.", resources);
  for (const auto &scene: scenesArray) scenes.push_back(scene.as_string());
}

void parsingError(const std::string &msg, const std::string &path) {
  Logger::error(msg);
  throw std::runtime_error("Check " + path);
}

void Engine::readScene(int index) {
  std::string path = resources + scenes[index];
  auto data = toml::parse(path + "/blueprint.toml");
  Logger::info("Trying to read " + path);
  if (data.is_uninitialized() || data["entities"].is_uninitialized())
    parsingError("Bad blueprint. Cannot load project. Exiting now.", path);
  const auto &entitiesArray = data["entities"].as_array();
  if (entitiesArray.empty())
    parsingError("No entities. Cannot load project. Exiting now.", path);
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
  if (components.empty() || entities.empty()) {
    Logger::error("Cannot run the engine. Components or entities are empty.");
    throw std::runtime_error("Please check the config.");
  }
  for (auto & physics_body : components["PhysicsBody"]) {
    auto physicsBody = dynamic_cast<PhysicsBodyComponent*>(physics_body);
    physicsBody->createBodyInWorld(world);
  }
  for (int i = 0; i < 200; i++) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    // [WIP] delta time should be passed to update instead of magic number
    systems.update({components, entities, renderer, world}, 1);
    SDL_RenderPresent(renderer);
    usleep(15000);
  }
}