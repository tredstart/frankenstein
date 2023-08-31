//
// Created by redstart on 8/25/23.
//
#include "../src/engine/engine.h"
#include "toml.hpp"
#include "gtest/gtest.h"
#include <filesystem>
#include "sol/sol.hpp"

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
  EXPECT_THROW(badKeys.readScene(0), toml::type_error);
  EXPECT_THROW(badValues.readScene(0), toml::type_error);
}

TEST(FrankensteinEngine, NumberOfCreatedEntitiesIsCorrect) {
  std::string path = "../../test_assets/resources/scene1/";
  int tomlFileCount = 0;

  for (const auto &entry: std::filesystem::directory_iterator(path))
    if (entry.is_regular_file() && entry.path().extension() == ".toml")
      tomlFileCount++;

  Engine engine;
  engine.readScene(0);
  ASSERT_EQ(engine.entities.size(), tomlFileCount - 1);
}

TEST(FrankensteinEngine, CannotRunWithoutComponentsOrEntities) {
  Engine engineWithEntities;
  engineWithEntities.readScene(0);
  engineWithEntities.components.clear();
  EXPECT_THROW(engineWithEntities.run(), std::runtime_error);

  Engine engineWithComponents;
  engineWithComponents.readScene(0);
  engineWithComponents.entities.clear();
  EXPECT_THROW(engineWithComponents.run(), std::runtime_error);
}


class Component {
public:
  int value;
};

TEST(FrankensteinEngine, RunLuaCode) {
  sol::state lua;
  auto component = new Component;
  component->value = 10;
  lua["component"] = component;
  lua.new_usertype<Component>("Component",
                           "value", &Component::value);
  for (int i = 0; i < 5; ++i) {
    lua.script("for i = 1, 2 do component.value = component.value + 1 end");
    ++component->value;
  }
  ASSERT_EQ(component->value, 25);
}