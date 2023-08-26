//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENTITY_H
#define FRANKENSTEIN_ENTITY_H

#include "components.h"
#include <cstdint>
#include <vector>
typedef uint64_t entity_id_t;

class Entity {
public:
  entity_id_t id;
  std::unordered_map<std::string, std::vector<IComponent *>> components;
  explicit Entity(entity_id_t id) { this->id = id; }
  ~Entity() = default;
};

#endif//FRANKENSTEIN_ENTITY_H
