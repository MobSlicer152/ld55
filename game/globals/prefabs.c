#include "game/components.h"

#include "game/systems/physics.h"

#include "misc.h"
#include "prefabs.h"
#include "sprites.h"

ecs_entity_t CreatePlayer(void)
{
    ecs_entity_t entity = ecs_new_entity(g_world, "player");
    ecs_set_ptr(g_world, entity, SPRITE, &s_player);
    PHYSICS_BODY body = {0};
    CreatePhysicsBody(&body, 0.0f, 0.0f, 0.0f, s_player.width / SPRITE_SIZE, s_player.height / SPRITE_SIZE,
                      PhysicsBodyTypeDynamic);
    ecs_set_ptr(g_world, entity, PHYSICS_BODY, &body);
    ecs_add(g_world, entity, PLAYER);

    return entity;
}

void CreateLevel(void)
{
#define PART(id, sprite, x, y, rotation, material, collision, type)                                                    \
    {                                                                                                                  \
        ecs_entity_t PART_##id = ecs_new_entity(g_world, #id);                                                         \
        ecs_set_ptr(g_world, PART_##id, SPRITE, (sprite));                                                             \
        PHYSICS_BODY body = {0};                                                                                       \
        CreatePhysicsBody(&body, (x) / SPRITE_SIZE, (y) / SPRITE_SIZE, 0.0f, (f32)(sprite)->width / SPRITE_SIZE,       \
                          (f32)(sprite)->height / SPRITE_SIZE, PhysicsBodyType##type);                                 \
        ecs_set_ptr(g_world, PART_##id, PHYSICS_BODY, &body);                                                          \
        ecs_add(g_world, PART_##id, LEVEL);                                                                            \
    }

    PART(ground, &s_ground, 0, 272, 0, nvMaterial_BASIC, true, Static);
    PART(ground2, &s_ground, 256, 272, 0, nvMaterial_BASIC, true, Static);

#undef PART
}
