#include "globals/misc.h"

#include "components.h"
#include "image.h"

ecs_entity_t ecs_id(TRANSFORM);

ecs_entity_t ecs_id(PHYSICS_BODY);

ecs_entity_t ecs_id(SPRITE);

void RegisterComponents(void)
{
    ECS_COMPONENT_DEFINE(g_world, TRANSFORM);

    ECS_COMPONENT_DEFINE(g_world, PHYSICS_BODY);

    ECS_COMPONENT_DEFINE(g_world, SPRITE);
}
