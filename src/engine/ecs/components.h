#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "toml/value.hpp"
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
class IComponent {
public:
  virtual ~IComponent() = default;
};


/*  Not standalone components  */
//
typedef struct {
  double width;
  double height;
} size_component_t;

typedef struct {
  double x;
  double y;
} position_component_t;

typedef struct {
  double x;
  double y;
} velocity_component_t;

typedef struct {
  position_component_t position;
  size_component_t size;
} rect_t;

typedef struct {
  position_component_t position;
  double radius;
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
  SpriteComponent(toml::table config, uint64_t entity_id);
  ~SpriteComponent() override = default;
};

class PhysicsBodyComponent : public IComponent {
public:
  collider_component_t collider{};
  uint64_t entity_id;
  PhysicsBodyComponent(toml::table config, uint64_t entity_id);
  ~PhysicsBodyComponent() override = default;
};

class TransformComponent : public IComponent {
public:
  position_component_t position{};
  velocity_component_t velocity{};
  uint64_t entity_id;
  TransformComponent(toml::table config, uint64_t entity_id);
  ~TransformComponent() override = default;
};

//
/* End of standalone components */

extern const std::unordered_map<
    std::string, std::function<IComponent*(toml::table, uint64_t)>>
    COMPONENTS_MAP;

#endif// !COMPONENTS_H
