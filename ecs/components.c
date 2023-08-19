#include "components.h"

sprite_component_t *components__new_sprite(
    position_component_t position,
    size_component_t size,
    uint64_t entity_id,
    char *texture
)
{
  sprite_component_t *sprite = calloc(1, sizeof(*sprite));
  if (!sprite)
    throw_error("Error! Cannot create sprite!");
  sprite->position = position;
  sprite->size = size;
  sprite->entity_id = entity_id;
  if (!sprite->texture)
    throw_error("Error! No texture!");
  sprite->texture = texture;
  return sprite;
}

physics_body_component_t *components__new_physics_body(
    void *shape,
    bool is_circular,
    uint64_t entity_id
)
{
  physics_body_component_t *physics_body = calloc(1, sizeof(*physics_body));
  if (!physics_body)
    throw_error("Error! Cannot create physics body");
  physics_body->is_circular = is_circular;
  if (physics_body->is_circular)
    physics_body->collider.circle = *(circle_t *) shape;
  else
    physics_body->collider.rect = *(rect_t *) shape;
  physics_body->entity_id = entity_id;
  return physics_body;
}

transform_component_t *components__new_transform_component(
    position_component_t position,
    velocity_component_t velocity,
    uint64_t entity_id
)
{
  transform_component_t *transform = calloc(1, sizeof(*transform));
  if (!transform)
    throw_error("Error! Cannot create sprite!");

  transform->position = position;
  transform->velocity = velocity;
  transform->entity_id = entity_id;
  return transform;
}