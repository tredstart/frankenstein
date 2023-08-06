#include "ecs/systems.h"
#include "core/vector.h"
#include "engine/engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 1024
#define HEIGHT 720

int main() {


  engine_s *engine = engine__new();
  sprite_component_t c1;
  sprite_component_t c2;
  create_empty_rectangle(&c1, 1);
  create_empty_rectangle(&c2, 2);
  c2.position.x += 10;



  engine->components[SPRITE] = vector__new(&c1);
  vector__add(engine->components[SPRITE], &c2);
  for (int i = 0; i < 10000; i++) {
    systems_update(engine);
    SDL_RenderPresent(engine->renderer);
  }

  SDL_DestroyRenderer(engine->renderer);
  SDL_DestroyWindow(engine->screen);
  // Quit SDL
  engine__drop(engine);
  SDL_Quit();

  return 0;
}
