//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_ENTITY_H
#define FRANKENSTEIN_ENTITY_H

#include <stdint.h>
#include "../core/vector.h"
#include "components.h"

typedef uint64_t entity_id_t;

typedef struct entity_t {
  entity_id_t id;
  vector *components[COMPONENTS_COUNT];
} entity_t;

#endif //FRANKENSTEIN_ENTITY_H
