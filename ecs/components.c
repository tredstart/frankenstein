#include "components.h"

sprite_component_t *components__new_sprite(
    position_component_t position,
    size_component_t size,
    entity_t entity_id,
    char *texture
) {
  sprite_component_t *sprite = calloc(1, sizeof(*sprite));
  if (!sprite)
    throw_error("Error! Cannot create sprite!");
  sprite->position = position;
  sprite->size = size;
  sprite->entity_id = entity_id;
  // todo: no texture no candy
  sprite->texture = texture;
  return sprite;
}

physics_body_component_t *components__new_physics_body(
    void *shape,
    bool is_circular,
    entity_t entity_id
) {
  physics_body_component_t *physics_body = calloc(1, sizeof(*physics_body));
  physics_body->is_circular = is_circular;
  if (physics_body->is_circular)
    physics_body->collider.circle = *(circle_t *) shape;
  else
    physics_body->collider.rect = *(SDL_Rect *) shape;
  physics_body->entity_id = entity_id;
  return physics_body;
}