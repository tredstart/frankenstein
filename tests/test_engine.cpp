//
// Created by redstart on 8/25/23.
//
#include "../src/engine/engine.h"
#include "toml.hpp"
#include "gtest/gtest.h"
#include <filesystem>

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

//TEST(FrankensteinEngine, CreatedWorld) {
//  b2Vec2 gravity(0.0f, -10.0f);
//  b2World world(gravity);
//  Engine engine(world);
//
//  // create ground box
//  // With the body definition we specify the initial position of the ground body.
//  b2BodyDef groundBodyDef;
//  groundBodyDef.position.Set(0.0f, -10.0f);
//  b2Body *groundBody = engine.world.CreateBody(&groundBodyDef);
//
//  // adding shape e.g. size
//  b2PolygonShape groundBox;
//  groundBox.SetAsBox(50.0f, 10.0f);
//
//  //We finish the ground body in step 4 by creating the shape fixture.
//  // For this step we have a shortcut. We do not have a need to alter the
//  // default fixture material properties, so we can pass the shape directly to
//  // the body without creating a fixture definition. Later we will see how to
//  // use a fixture definition for customized material properties. The second
//  // parameter is the shape density in kilograms per meter squared. A static
//  // body has zero mass by definition, so the density is not used in this case.
//  groundBody->CreateFixture(&groundBox, 0.0f);
//
//  // creating a dynamic body
//  // First we create the body using CreateBody. By default, bodies are static,
//  // so we should set the b2BodyType at construction time to make the body
//  // dynamic
//  b2BodyDef bodyDef;
//  bodyDef.type = b2_dynamicBody;
//  bodyDef.position.Set(0.0f, 4.0f);
//  b2Body* body = engine.world.CreateBody(&bodyDef);
//
//  // Next we create and attach a polygon shape using a fixture definition.
//  // First we create a box shape:
//  b2PolygonShape dynamicBox;
//  dynamicBox.SetAsBox(1.0f, 1.0f);
//
//  b2FixtureDef fixtureDef;
//  fixtureDef.shape = &dynamicBox;
//  fixtureDef.density = 1.0f;
//  fixtureDef.friction = 0.3f;
//
//  body->CreateFixture(&fixtureDef);
//
//  // simulating the world
//  float timeStep = 1.0f / 60.0f;
//  int32 velocityIterations = 6;
//  int32 positionIterations = 2;
//  b2Vec2 prevPos = body->GetPosition();
//  for (int32 i = 0; i < 60; ++i) {
//    engine.world.Step(timeStep, velocityIterations, positionIterations);
//    b2Vec2 position = body->GetPosition();
//    ASSERT_GT(position.y, prevPos.y);
//  }
//}