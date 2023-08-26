//
// Created by redstart on 8/5/23.
//

#ifndef FRANKENSTEIN_UTILS_H
#define FRANKENSTEIN_UTILS_H

#include <string>
class Logger {
public:
  static void info(const std::string &msg);
  static void error(const std::string &msg);
};

#endif// FRANKENSTEIN_UTILS_H
