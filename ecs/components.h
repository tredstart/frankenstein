#ifndef COMPONENTS_H

#include <SDL2/SDL_rect.h>
#include <stdbool.h>
/*  Not standalone components  */
//

typedef struct {
  int width;
  int height;
} size_component_t;

typedef struct {
  int x;
  int y;
} position_component_t;

typedef struct {
  int x;
  int y;
} velocity_component_t;

typedef struct {
  position_component_t position;
  float radius;
} circle_t;

/* [WIP] */
/* if there is need to render out the collider, SDL_rect is easy to pass */
/* it is topic to consider */
typedef struct {
  SDL_Rect rect;
  circle_t circle;
} collider_component_t;

//
/* End of not standalone components */

/* Standalone components */
//

typedef struct {
  position_component_t position;
  size_component_t size;
  int entity_id;
  char *texture;
} sprite_component_t;

typedef struct {
  collider_component_t collider;
  bool is_circular;
  int entity_id;
} physics_body_component_t;

typedef struct {
  position_component_t position;
  velocity_component_t velocity;
  int entity_id;
} transform_component_t;

//
/* End of not standalone components */

typedef enum {
  SIZE = 0,
  TRANSFORM,
  SPRITE,
  PHYSICS_BODY,

  COMPONENTS_COUNT
} components_e;

sprite_component_t *components__new_sprite(
    position_component_t position,
    size_component_t size,
    int entity_id,
    char *texture
);

physics_body_component_t *components__new_physics_body(
    void *shape,
    bool is_circular,
    int entity_id
);


#endif // !COMPONENTS_H
