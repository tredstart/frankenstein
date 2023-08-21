//
// Created by redstart on 8/5/23.
//

#include "engine.h"


Engine::Engine() {
  this->screen = nullptr;

  // [WIP] create test data
  entity_t *e1 = static_cast<entity_t *>(calloc(1, sizeof(*e1)));
  entity_t *e2 = static_cast<entity_t *>(calloc(1, sizeof(*e2)));
  e1->id = 0;
  e2->id = 1;

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

  sprite_component_t *c1 = componentsNewSprite(p1, s1, e1->id, nullptr);
  sprite_component_t *c2 = componentsNewSprite(p2, s2, e2->id, nullptr);

  SDL_Rect rect1 = {.x = c1->position.x, .y = c1->position.y, .w = c1->size.width, .h = c1->size.height };
  SDL_Rect rect2 = {.x = c2->position.x, .y = c2->position.y, .w = c2->size.width, .h = c2->size.height };
  physics_body_component_t *cc1 = componentsNewPhysicsBody(&rect1, false, e1->id);
  physics_body_component_t *cc2 = componentsNewPhysicsBody(&rect2, false, e2->id);

  velocity_component_t velocity1 = {.x = 0, .y = 10};
  velocity_component_t velocity2 = {.x = 0, .y = 0};
  transform_component_t *tc1 = componentsNewTransformComponent(c1->position, velocity1, e1->id);
  transform_component_t *tc2 = componentsNewTransformComponent(c2->position, velocity2, e2->id);
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

void Engine::addComponent(void *component, components_e index) {
  this->components[index].push_back(component);
}
