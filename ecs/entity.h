//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENTITY_H
#define FRANKENSTEIN_ENTITY_H

#include <cstdint>
#include "components.h"

typedef uint64_t entity_id_t;

typedef struct entity_t {
public:
  entity_id_t id;
  std::vector<void*> components[COMPONENTS_COUNT];
} entity_t;

#endif //FRANKENSTEIN_ENTITY_H
