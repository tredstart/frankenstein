#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "box2d/box2d.h"
#include "toml/value.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
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
//typedef struct {
//  double width;
//  double height;
//} size_component_t;
//
//typedef struct {
//  double x;
//  double y;
//} position_component_t;

//
/* End of not standalone components */

/* Standalone components */
//

class SpriteComponent : public IComponent {
public:
  SDL_Rect destination;
  std::string texture_path;
  SDL_Surface* imageSurface{};
  SDL_Texture *texture{};
  uint64_t entity_id;
  void createTexture(SDL_Renderer *renderer, const std::string& resources);
  SpriteComponent(toml::table config, uint64_t entity_id);
  ~SpriteComponent() override {
      SDL_DestroyTexture(texture);
      SDL_FreeSurface(imageSurface);
  };

};

class PhysicsBodyComponent : public IComponent {
public:
  b2BodyDef bodyDefinition;
  b2FixtureDef fixtureDefinition;
  b2PolygonShape shape;
  b2Body *body{};
  uint64_t entity_id;
  PhysicsBodyComponent(toml::table config, uint64_t entity_id);
  void createBodyInWorld(b2World *world);
  ~PhysicsBodyComponent() override = default;
};



//
/* End of standalone components */

extern const std::unordered_map<
    std::string, std::function<IComponent*(toml::table, uint64_t)>>
    COMPONENTS_MAP;

#endif// !COMPONENTS_H
