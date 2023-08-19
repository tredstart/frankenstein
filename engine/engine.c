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
  e1->id = 1;
  e2->id = 2;

  engine->entities = hash_map__new();
  hash_map__insert(engine->entities, e1->id, e1->components);
  hash_map__insert(engine->entities, e2->id, e2->components);

  sprite_component_t *c1 = create_empty_rectangle(e1->id);
  sprite_component_t *c2 = create_empty_rectangle(e2->id);
  c2->position.x += 10;

  SDL_Rect rect1 = {.x = c1->position.x, .y = c1->position.y, .w = c1->size.width, .h = c1->size.height };
  SDL_Rect rect2 = {.x = c2->position.x, .y = c2->position.y, .w = c2->size.width, .h = c2->size.height };
  physics_body_component_t *cc1 = components__new_physics_body(&rect1, false, 1);
  physics_body_component_t *cc2 = components__new_physics_body(&rect2, false, 2);

  e1->components[SPRITE] = vector__new(c1);
  e1->components[PHYSICS_BODY] = vector__new(cc1);
  e2->components[SPRITE] = vector__new(c2);
  e2->components[PHYSICS_BODY] = vector__new(cc2);

  engine__add_component(engine, c1, SPRITE);
  engine__add_component(engine, c2, SPRITE);
  engine__add_component(engine, cc1, PHYSICS_BODY);
  engine__add_component(engine, cc2, PHYSICS_BODY);

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &engine->screen,
                              &engine->renderer);

  return engine;
}

void engine__drop(engine_s *self) {
  for (int i = 0; i < COMPONENTS_COUNT; ++i)
    vector__drop(self->components[i]);
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

// todo remove this later
sprite_component_t *create_empty_rectangle(uint64_t entity_id) {
  position_component_t pos = {.x = 10, .y = 10};
  size_component_t size = {.width = 100, .height = 100};
  sprite_component_t *component = components__new_sprite(pos, size, entity_id, NULL);
  return component;
}