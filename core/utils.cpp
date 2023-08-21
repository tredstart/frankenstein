//
// Created by redstart on 8/5/23.
//

#include "utils.h"
#include <iostream>

void throw_error(const char *msg) {
  std::cerr << msg << std::endl;
  exit(EXIT_FAILURE);
}