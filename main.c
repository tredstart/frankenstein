#include "ecs/systems.h"
#include "core/vector.h"
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

  sprite_component_t c1;
  sprite_component_t c2;
  create_empty_rectangle(&c1, 1);
  create_empty_rectangle(&c2, 2);
  c2.position.x += 10;

  vector *components[ENUM_LENGTH];
  components[SPRITE] = vector__new(&c1);
  vector__add(components[SPRITE], &c2);

  for (int i = 0; i < 10000; i++) {
    render_system(components[SPRITE], renderer);
    SDL_RenderPresent(renderer);
  }
  vector__drop(components[SPRITE]);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  // Quit SDL
  SDL_Quit();

  return 0;
}
