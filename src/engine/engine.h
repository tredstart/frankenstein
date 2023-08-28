//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENGINE_H
#define FRANKENSTEIN_ENGINE_H

#include "box2d/box2d.h"
#include "ecs/entity.h"
#include "ecs/systems.h"
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"

class Engine {
private:
  Systems systems;
  void loadScenes();
  void parseEntity(const std::string &name);
  std::vector<std::string> scenes;
  std::string resources;

public:
  explicit Engine(const std::string &resources =
                                            "../../test_assets/resources/");
  void readScene(int index = 0);
  void run();
  ~Engine();

  sf::RenderWindow *window;
  bool debug = true;
  std::unordered_map<std::string, std::vector<IComponent *>> components;
  std::unordered_map<uint64_t, Entity *> entities;
  b2World *world;
};
#endif// FRANKENSTEIN_ENGINE_H
