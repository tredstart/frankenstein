#ifndef COMPONENTS_H

#include <SDL2/SDL_rect.h>
#include "../core/utils.h"
/*  Not standalone components  */
//

typedef struct size_component_t {
  int width;
  int height;
} size_component_t;

typedef struct position_component_t {
  int x;
  int y;
} position_component_t;

typedef struct velocity_component_t {
  int x;
  int y;
} velocity_component_t;

typedef struct rect_t {
  position_component_t position;
  size_component_t size;
} rect_t;

typedef struct circle_t {
  position_component_t position;
  float radius;
} circle_t;

typedef struct collider_component_t {
  rect_t rect;
  circle_t circle;
} collider_component_t;

//
/* End of not standalone components */

/* Standalone components */
//

typedef struct sprite_component_t {
  position_component_t position;
  size_component_t size;
  uint64_t entity_id;
  char *texture;
} sprite_component_t;

typedef struct physics_body_component_t {
  collider_component_t collider;
  bool is_circular;
  uint64_t entity_id;
} physics_body_component_t;

typedef struct transform_component_t {
  position_component_t position;
  velocity_component_t velocity;
  uint64_t entity_id;
} transform_component_t;

//
/* End of standalone components */

typedef enum {
  TRANSFORM,
  SPRITE,
  PHYSICS_BODY,

  COMPONENTS_COUNT
} components_e;

sprite_component_t *componentsNewSprite(
    position_component_t position,
    size_component_t size,
    uint64_t entity_id,
    char *texture
);

physics_body_component_t *componentsNewPhysicsBody(
    void *shape,
    bool is_circular,
    uint64_t entity_id
);

transform_component_t *componentsNewTransformComponent(
    position_component_t position,
    velocity_component_t velocity,
    uint64_t entity_id
);


#endif // !COMPONENTS_H
