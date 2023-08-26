//
// Created by redstart on 8/25/23.
//
#include "../src/engine/engine.h"
#include "toml.hpp"
#include "gtest/gtest.h"

TEST(FrankensteinEngine, LoadWrongOrEmptyScenesThrowsErrors) {
  EXPECT_THROW(Engine("../../test_assets/emptyResources/"), std::runtime_error);
  EXPECT_THROW(Engine("../../test_assets/noScenes/"), std::runtime_error);
}
TEST(FrankensteinEngine, ReadWrongOrEmptyScenesThrowsErrors) {
  Engine emptyScene("../../test_assets/emptyScene/");
  Engine emptyBlueprint("../../test_assets/emptyBlueprint/");
  Engine emptyEntity("../../test_assets/emptyEntity/");
  EXPECT_THROW(emptyScene.readScene(0), std::runtime_error);
  EXPECT_THROW(emptyBlueprint.readScene(0), std::runtime_error);
  EXPECT_THROW(emptyEntity.readScene(0), std::runtime_error);
}

TEST(FrankensteinEngine, LoadBadComponentsThrowsErrors) {
  Engine badKeys("../../test_assets/badKeys/");
  Engine badValues("../../test_assets/badValues/");
  EXPECT_THROW(badKeys.readScene(0), std::out_of_range);
  EXPECT_THROW(badValues.readScene(0), toml::type_error);
}

//TEST(FrankensteinEngine, RunsCorrectlyWithTestData) {
//  Engine engine;
//  engine.readScene(0);
//  engine.run();
//}