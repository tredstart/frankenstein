//
// Created by redstart on 8/26/23.
//

#include "gtest/gtest.h"
#include "../src/engine/engine.h"

TEST(EngineSystems, RenderSystemDoesNotFail) {
  Engine engine;
  engine.readScene(0);
  render_system(Context{
      engine.components,
      engine.entities,
      engine.renderer
  }, 1);
}