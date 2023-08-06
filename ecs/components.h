#ifndef COMPONENTS_H

typedef struct {
  int width;
  int height;
  int x;
  int y;
} collider_component_t;

typedef struct {
  int width;
  int height;
} size_component_t;

typedef struct {
  int x;
  int y;
} position_component_t;

typedef struct {
  position_component_t position;
  size_component_t size;
  int entity_id;
  char *texture;
} sprite_component_t;

typedef enum {
  SIZE = 0,
  COLLIDER,
  POSITION,
  SPRITE,

  COMPONENTS_COUNT
} components_e;

#endif // !COMPONENTS_H
