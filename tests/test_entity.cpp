//
// Created by redstart on 8/31/23.
//

#include "../src/engine/engine.h"
#include <gtest/gtest.h>

class TestComponent : public IComponent {
public:
  int value;
  explicit TestComponent(int v) { value = v; }
  ~TestComponent() override = default;
};

const std::string lua_script = R"lua(

local test_component = self:GetComponent("TestComponent")
test_component.value = 10
function update(dt)
  test_component.value = test_component.value * dt
end

)lua";


TEST(FrankensteinEngine, EntityGetComponentReturnsCorrectComponentInLuaScript) {
  sol::state lua;
  Entity entity(1);
  TestComponent testComponent(0);
  entity.components["TestComponent"].push_back(&testComponent);
  lua.new_usertype<TestComponent>("TestComponent",
                                  "value", &TestComponent::value);
  lua.new_usertype<Entity>("Entity",
                           "GetComponent", sol::overload(&Entity::GetComponent<TestComponent>));
  lua["self"] = entity;
  lua.script(lua_script);
  ASSERT_EQ(testComponent.value, 10);
  lua["update"](2);
  ++testComponent.value;
  ASSERT_EQ(testComponent.value, 21);
}