//
// Created by redstart on 8/5/23.
//

#include "engine.h"
#include "consts.h"
#include <SDL2/SDL.h>


Engine::Engine() {
  this->screen = nullptr;

  // [WIP] create test data
  auto e1 = new Entity(0);
  auto e2 = new Entity(1);

  entities.insert_or_assign(e1->id, e1);
  entities.insert_or_assign(e2->id, e2);

  position_component_t p1 = {
      .x = 500,
      .y = 100,
  };
  size_component_t s1 = {100, 100};

  position_component_t p2 = {
      .x = 500,
      .y = 500,
  };
  size_component_t s2 = {100, 100};

  auto c1 = new SpriteComponent(p1, s1, e1->id, nullptr);
  auto c2 = new SpriteComponent(p2, s2, e2->id, nullptr);

  rect_t rect1 = {.position = c1->position, .size = c1->size};
  rect_t rect2 = {.position = c2->position, .size = c2->size};
  auto cc1 = new PhysicsBodyComponent(&rect1, false, e1->id);
  auto cc2 = new PhysicsBodyComponent(&rect2, false, e2->id);

  velocity_component_t velocity1 = {.x = 0, .y = 10};
  velocity_component_t velocity2 = {.x = 0, .y = 0};
  auto tc1 = new TransformComponent(c1->position, velocity1, e1->id);
  auto tc2 = new TransformComponent(c2->position, velocity2, e2->id);
  e1->components[SPRITE].push_back(c1);
  e1->components[PHYSICS_BODY].push_back(cc1);
  e1->components[TRANSFORM].push_back(tc1);
  e2->components[SPRITE].push_back(c2);
  e2->components[PHYSICS_BODY].push_back(cc2);
  e2->components[TRANSFORM].push_back(tc2);

  addComponent(c1, SPRITE);
  addComponent(c2, SPRITE);
  addComponent(cc1, PHYSICS_BODY);
  addComponent(cc2, PHYSICS_BODY);
  addComponent(tc1, TRANSFORM);
  addComponent(tc2, TRANSFORM);

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
