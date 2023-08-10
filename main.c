#include "core/vector.h"
#include "ecs/systems.h"
#include "engine/engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <unistd.h>

#define WIDTH 1024
#define HEIGHT 720

int main() {

  engine_s *engine = engine__new();

  for (int i = 0; i < 60; i++) {
    SDL_SetRenderDrawColor(engine->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(engine->renderer);
    systems_update(engine, 1);
    SDL_RenderPresent(engine->renderer);
    usleep(15000);
  }

  SDL_DestroyRenderer(engine->renderer);
  SDL_DestroyWindow(engine->screen);
  // Quit SDL
  engine__drop(engine);
  SDL_Quit();

  return 0;
}
