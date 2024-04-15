#include "globals/misc.h"

#include "components.h"
#include "image.h"

ecs_entity_t ecs_id(POSITION);
ecs_entity_t ecs_id(ROTATION);

ecs_entity_t ecs_id(PHYSICS_BODY);

ecs_entity_t ecs_id(HEALTH);

ecs_entity_t ecs_id(PLAYER);
ecs_entity_t ecs_id(PROJECTILE_TYPE);
ecs_entity_t ecs_id(PROJECTILE_MAX_HITS);
ecs_entity_t ecs_id(PROJECTILE_COOLDOWN);

ecs_entity_t ecs_id(ANIMATION);
ecs_entity_t ecs_id(FLIP);
ecs_entity_t ecs_id(SPRITE);

#define MAKE_ECS_TAG(id)                                                                                               \
    ecs_entity_t ecs_id(id);                                                                                           \
    ecs_entity_t id;

MAKE_ECS_TAG(LEVEL);

void RegisterComponents(void)
{
    ECS_COMPONENT_DEFINE(g_world, POSITION);
    ECS_COMPONENT_DEFINE(g_world, ROTATION);

    ECS_COMPONENT_DEFINE(g_world, PHYSICS_BODY);


    ECS_COMPONENT_DEFINE(g_world, ANIMATION);
    ECS_COMPONENT_DEFINE(g_world, FLIP);
    ECS_COMPONENT_DEFINE(g_world, SPRITE);

    ECS_COMPONENT_DEFINE(g_world, PLAYER);
    ECS_COMPONENT_DEFINE(g_world, PROJECTILE_TYPE);
    ECS_COMPONENT_DEFINE(g_world, PROJECTILE_MAX_HITS);
    ECS_COMPONENT_DEFINE(g_world, PROJECTILE_COOLDOWN);

    ECS_TAG_DEFINE(g_world, LEVEL);
}
