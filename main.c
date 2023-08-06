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
  SDL_Window *screen = NULL;
  SDL_Renderer *renderer;
  SDL_Event event;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen,
                              &renderer);

  engine_s *engine = engine__new();

  for (int i = 0; i < 10000; i++) {
    systems_update(engine);
    SDL_RenderPresent(renderer);
  }
  vector__drop(engine->components[SPRITE]);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  // Quit SDL
  SDL_Quit();

  return 0;
}
