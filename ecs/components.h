#ifndef COMPONENTS_H

#include "../core/utils.h"
#include <SDL2/SDL_rect.h>

class IComponent {
public:
  virtual ~IComponent() = default;
};


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
  size_component_t size;
} rect_t;

typedef struct {
  position_component_t position;
  float radius;
} circle_t;

typedef struct {
  rect_t rect;
  circle_t circle;
} collider_component_t;

//
/* End of not standalone components */

/* Standalone components */
//

class SpriteComponent : public IComponent {
public:
  position_component_t position{};
  size_component_t size{};
  uint64_t entity_id;
  char *texture;
  SpriteComponent(position_component_t position, size_component_t size,
                  uint64_t entity_id, char *texture);
  ~SpriteComponent() override = default;
};

class PhysicsBodyComponent : public IComponent {
public:
  collider_component_t collider{};
  bool is_circular;
  uint64_t entity_id;
  PhysicsBodyComponent(void *shape, bool is_circular, uint64_t entity_id);
  ~PhysicsBodyComponent() override = default;
};

class TransformComponent : public IComponent {
public:
  position_component_t position{};
  velocity_component_t velocity{};
  uint64_t entity_id;
  TransformComponent(position_component_t position,
                     velocity_component_t velocity, uint64_t entity_id);
  ~TransformComponent() override = default;
};

//
/* End of standalone components */

typedef enum {
  TRANSFORM,
  SPRITE,
  PHYSICS_BODY,

  COMPONENTS_COUNT
} components_e;


#endif// !COMPONENTS_H
