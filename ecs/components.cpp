#include "components.h"

SpriteComponent::SpriteComponent(position_component_t position,
                                 size_component_t size, uint64_t entity_id,
                                 char *texture) {
  this->position = position;
  this->size = size;
  this->entity_id = entity_id;
  // [WIP] for early testing purposes
  //  if (!sprite->texture)
  //    throw_error("Error! No texture!");
  this->texture = texture;
}

PhysicsBodyComponent::PhysicsBodyComponent(rect_t shape, bool is_circular,
                                           uint64_t entity_id) {
  this->is_circular = is_circular;
//  if (this->is_circular) this->collider.circle = *(circle_t *) shape;
//  else
    this->collider.rect = shape;
  this->entity_id = entity_id;
}
TransformComponent::TransformComponent(position_component_t position,
                                       velocity_component_t velocity,
                                       uint64_t entity_id) {
  this->position = position;
  this->velocity = velocity;
  this->entity_id = entity_id;
}
