#ifndef COMPONENTS_H
#include <SDL2/SDL_rect.h>


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
} physics_body_component_t;

typedef struct {
  position_component_t position;
  velocity_component_t velocity;
} transform_component_t;

//
/* End of not standalone components */

typedef enum {
  SIZE = 0,
  COLLIDER,
  TRANSFORM,
  SPRITE,
  PHYSICS_BODY,
  
  COMPONENTS_COUNT
} components_e;



#endif // !COMPONENTS_H
