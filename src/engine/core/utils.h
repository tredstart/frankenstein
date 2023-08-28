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

float toPixels(float inMeters);

template<typename T>
T toPixels(T vector) {
  return T(toPixels(vector.x), toPixels(vector.y));
}

float toMeters(float inPixels);

// returns a cast vector from T to N
template<typename N, typename T>
N as_vector(const T &old_vector) {
  return N(old_vector.x, old_vector.y);
}

#endif// FRANKENSTEIN_UTILS_H
