//
// Created by redstart on 8/5/23.
//

#include "engine.h"
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
  engine->systems[RENDER] = systems__new(engine->systems[RENDER], &render_system);
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