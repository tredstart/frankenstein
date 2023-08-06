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

  sprite_component_t c1;
  sprite_component_t c2;
  create_empty_rectangle(&c1, 1);
  create_empty_rectangle(&c2, 2);
  c2.position.x += 10;


  engine->systems[RENDER] = systems__new(engine->systems[RENDER], &render_system);
  engine->components[SPRITE] = vector__new(&c1);
  vector__add(engine->components[SPRITE], &c2);
  return engine;
}