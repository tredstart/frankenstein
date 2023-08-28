//
// Created by redstart on 8/26/23.
//

#include "../src/engine/engine.h"
#include "gtest/gtest.h"

TEST(EngineSystems, RenderSystemDoesNotFail) {
  Engine engine;
  engine.readScene(0);
  render_system(
      Context{engine.components, engine.entities, engine.window, engine.world},
      1);
}