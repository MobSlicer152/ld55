#include "components.h"
#include "globals.h"
#include "spritesheet.h"

ecs_entity_t ecs_id(nvBody);

ecs_entity_t ecs_id(SPRITE);

void RegisterComponents(void)
{
    ECS_COMPONENT_DEFINE(g_world, nvBody);
    
    ECS_COMPONENT_DEFINE(g_world, SPRITE);
}
