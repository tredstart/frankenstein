//
// Created by redstart on 8/5/23.
//

#include "engine.h"


engine_s *engine__new() {
  engine_s *engine = calloc(1, sizeof(*engine));

  if (!engine)
    // todo: make proper logs with stderr
    throw_error("Error! Cannot create engine;");

  engine->screen = NULL;

  // [WIP] create test data
  entity_t *e1 = calloc(1, sizeof(*e1));
  entity_t *e2 = calloc(1, sizeof(*e2));
  e1->id = 0;
  e2->id = 1;

  engine->entities = hash_map__new();
  hash_map__insert(engine->entities, e1->id, e1);
  hash_map__insert(engine->entities, e2->id, e2);

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

  sprite_component_t *c1 = components__new_sprite(p1, s1, e1->id, NULL);
  sprite_component_t *c2 = components__new_sprite(p2, s2, e2->id, NULL);

  SDL_Rect rect1 = {.x = c1->position.x, .y = c1->position.y, .w = c1->size.width, .h = c1->size.height };
  SDL_Rect rect2 = {.x = c2->position.x, .y = c2->position.y, .w = c2->size.width, .h = c2->size.height };
  physics_body_component_t *cc1 = components__new_physics_body(&rect1, false, e1->id);
  physics_body_component_t *cc2 = components__new_physics_body(&rect2, false, e2->id );

  velocity_component_t velocity1 = {.x = 0, .y = 10};
  velocity_component_t velocity2 = {.x = 0, .y = 0};
  transform_component_t *tc1 = components__new_transform_component(c1->position, velocity1, e1->id);
  transform_component_t *tc2 = components__new_transform_component(c2->position, velocity2, e2->id);
  e1->components[SPRITE] = vector__new(c1);
  e1->components[PHYSICS_BODY] = vector__new(cc1);
  e1->components[TRANSFORM] = vector__new(tc1);
  e2->components[SPRITE] = vector__new(c2);
  e2->components[PHYSICS_BODY] = vector__new(cc2);
  e2->components[TRANSFORM] = vector__new(tc2);

  engine__add_component(engine, c1, SPRITE);
  engine__add_component(engine, c2, SPRITE);
  engine__add_component(engine, cc1, PHYSICS_BODY);
  engine__add_component(engine, cc2, PHYSICS_BODY);
  engine__add_component(engine, tc1, TRANSFORM);
  engine__add_component(engine, tc2, TRANSFORM);

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &engine->screen,
                              &engine->renderer);

  return engine;
}

void engine__drop(engine_s *self) {
  for (int i = 0; i < COMPONENTS_COUNT; ++i)
    vector__drop(self->components[i]);
  // todo: address memory leak
//  for (int i = 0; i < self->entities->count; ++i)
//    delete(self->entities->map[i].value);
  hash_map__drop(self->entities);
  delete(self);
}

void engine__add_component(engine_s *self, void *component,
                           components_e index) {
  if (self->components[index])
    vector__add(self->components[index], component);
  else
    self->components[index] = vector__new(component);
}
