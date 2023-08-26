

#include "engine/ecs/systems.h"
#include "engine/engine.h"
#include <SDL2/SDL.h>
#include <csignal>
int main() {

  auto *engine = new Engine;
  Systems systems;
  for (int i = 0; i < 100; i++) {
    SDL_SetRenderDrawColor(engine->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(engine->renderer);
    // [WIP] delta time should be passed to update instead of magic number
    systems.update({
                       engine->components,
                       engine->entities,
                       engine->renderer
                   }, 1);
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
