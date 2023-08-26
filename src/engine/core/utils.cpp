//
// Created by redstart on 8/5/23.
//

#include "utils.h"
#include <chrono>
#include <iostream>

void Logger::error(const std::string &msg) {
  std::cerr << "[ERROR " << std::chrono::system_clock::now() << "] " << msg
            << std::endl;
}
void Logger::info(const std::string &msg) {
  std::cout << "[INFO " << std::chrono::system_clock::now() << "] " << msg
            << std::endl;
}
