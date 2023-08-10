//
// Created by redstart on 8/5/23.
//

#include "engine.h"
#include "../core/utils.h"

#define WIDTH 1024
#define HEIGHT 720

void systems_update(void *engine, float dt) {
  engine_s *self = engine;
  for (int i = 0; i < SYSTEMS_COUNT; ++i) {
    systems_i *system = self->systems[i];
    system->update(self, dt);
  }
}

engine_s *engine__new() {
  engine_s *engine = calloc(1, sizeof(*engine));

  if (!engine)
    // todo: make proper logs with stderr
    throw_error("Error! Cannot create engine;");

  engine->screen = NULL;

  // [WIP] create test data
  sprite_component_t *c1 = create_empty_rectangle(1);
  sprite_component_t *c2 = create_empty_rectangle(2);
  c2->position.x += 10;

  engine__add_component(engine, c1, SPRITE);
  engine__add_component(engine, c2, SPRITE);

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &engine->screen,
                              &engine->renderer);
  engine__add_system(engine, engine->systems[RENDER], RENDER, &render_system);
  return engine;
}

void engine__drop(engine_s *self) {
  for (int i = 0; i < COMPONENTS_COUNT; ++i)
    vector__drop(self->components[i]);

  for (int i = 0; i < SYSTEMS_COUNT; ++i)
    systems__drop(self->systems[i]);

  delete(self);
}

void engine__add_component(engine_s *self, void *component,
                           components_e index) {
  if (self->components[index])
    vector__add(self->components[index], component);
  else
    self->components[index] = vector__new(component);
}

void engine__add_system(engine_s *self, systems_i *system, systems_e index,
                        void(*update_func)) {
  if (!self->systems[index])
    self->systems[index] = systems__new(system, update_func);
  else
    throw_error("Error! Cannot change existing system.");
}
