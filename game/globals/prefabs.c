#include "game/components.h"

#include "misc.h"
#include "prefabs.h"
#include "sprites.h"

ecs_entity_t CreatePlayer(void)
{
    ecs_entity_t entity = ecs_new_entity(g_world, "player");
    ecs_set_ptr(g_world, entity, SPRITE, &s_player);
    PHYSICS_BODY body = {nvBody_new(nvBodyType_DYNAMIC, nvRectShape_new(s_player.width, s_player.height), NV_VEC2(0.0f, 0.0f), 0.0f, nvMaterial_BASIC)};
    nvSpace_add(g_space, body.body);
    ecs_set_ptr(g_world, entity, PHYSICS_BODY, &body);
    ecs_add(g_world, entity, PLAYER);

    return entity;
}

void CreateLevel(void)
{
#define PART(id, sprite, x, y, rotation, material, collision)                                                                                               \
    {                                                                                                                                                       \
        ecs_entity_t PART_##id = ecs_new_entity(g_world, #id);                                                                                              \
        ecs_set_ptr(g_world, PART_##id, SPRITE, (sprite));                                                                                                  \
        PHYSICS_BODY body = {nvBody_new(nvBodyType_STATIC, nvRectShape_new((sprite)->width, (sprite)->height), NV_VEC2((x), (y)), (rotation), (material))}; \
        nvSpace_add(g_space, body.body);                                                                                                                    \
        ecs_set_ptr(g_world, PART_##id, PHYSICS_BODY, &body);                                                                                               \
        ecs_add(g_world, PART_##id, LEVEL);                                                                                                                 \
    }

    PART(ground, &s_ground, 0, 240, 0, nvMaterial_CONCRETE, true);

#undef PART
}
