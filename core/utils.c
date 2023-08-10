//
// Created by redstart on 8/5/23.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void throw_error(const char *msg) {
  printf("%s", msg);
  exit(1);
}

void delete(void *object) {
  free(object);
  object = NULL;
}
