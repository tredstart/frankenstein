//
// Created by redstart on 8/5/23.
//

#include "engine.h"
#include "../core/utils.h"

#define WIDTH 1024
#define HEIGHT 720
void systems_update(void *engine) {
  engine_s *self = (engine_s *)engine;
  for (int i = 0; i < SYSTEMS_COUNT; ++i) {
    systems_i *system = self->systems[i];
    system->update(self);
  }
}

engine_s *engine__new() {
  engine_s *engine = (engine_s*) calloc(1, sizeof(*engine));

  engine->screen = NULL;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &engine->screen,
                              &engine->renderer);
  engine__add_system(engine, engine->systems[RENDER], RENDER, &render_system);
  return engine;
}

void engine__drop(engine_s *self) {
  for (int i = 0; i < COMPONENTS_COUNT; ++i) {
    vector__drop(self->components[i]);
  }
  for (int i = 0; i < SYSTEMS_COUNT; ++i) {
    systems__drop(self->systems[i]);
  }
  free(self);
  self = NULL;
}

void engine__add_component(engine_s *self, void *component, components_e index) {
  if (self->components[index]){
    vector__add(self->components[index], component);
  }else {
    self->components[index] = vector__new(component);
  }
}

void engine__add_system(engine_s *self, systems_i *system, systems_e index, void (*update_func)) {
  if (!self->systems[index])
    self->systems[index] = systems__new(system, update_func);
  else
    throw_error("Error! Cannot change existing system.");
}