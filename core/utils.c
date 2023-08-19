//
// Created by redstart on 8/5/23.
//

#include "utils.h"

void throw_error(const char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}