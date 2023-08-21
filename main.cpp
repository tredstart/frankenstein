#include "ecs/systems.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <unistd.h>

int main() {

  auto *engine = new Engine;

  for (int i = 0; i < 60; i++) {
    SDL_SetRenderDrawColor(engine->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(engine->renderer);
    systems__update(engine, 1);
    SDL_RenderPresent(engine->renderer);
    usleep(15000);
  }

  SDL_DestroyRenderer(engine->renderer);
  SDL_DestroyWindow(engine->screen);
  // Quit SDL
  delete engine;
  SDL_Quit();

  return 0;
}
