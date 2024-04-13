#include "game/components.h"

#include "game/systems/physics.h"

#include "misc.h"
#include "prefabs.h"
#include "sprites.h"

ecs_entity_t CreatePlayer(f32 x, f32 y)
{
    ecs_entity_t entity = ecs_new_entity(g_world, "player");

    ecs_set_ptr(g_world, entity, SPRITE, &s_player);

    PHYSICS_BODY body = {0};

    PHYSICS_COLLIDER_DESC mainCollider = {.x = 0.0f,
                                          .y = 0.0f,
                                          .width = s_player.width / SPRITE_SIZE,
                                          .height = s_player.height / SPRITE_SIZE,
                                          .mass = PLAYER_MASS,
                                          .shape = PhysicsColliderShapeRect,
                                          .allowCollision = true};

    PHYSICS_COLLIDER_DESC colliders[] = {mainCollider};

    CreatePhysicsBody(&body, x, y, PhysicsBodyTypeDynamic, false, colliders, ARRAYSIZE(colliders));

    ecs_set_ptr(g_world, entity, PHYSICS_BODY, &body);
    ecs_add(g_world, entity, PLAYER);

    return entity;
}

void CreateLevel(void)
{
#define PART(id, sprite, x, y, rotation, type, shape_)                                                                 \
    {                                                                                                                  \
        ecs_entity_t PART_##id = ecs_new_entity(g_world, #id);                                                         \
        ecs_set_ptr(g_world, PART_##id, SPRITE, (sprite));                                                             \
        PHYSICS_BODY body = {0};                                                                                       \
        PHYSICS_COLLIDER_DESC desc = {                                                                                 \
            .zRotation = (rotation),                                                                                   \
            .width = (f32)(sprite)->width / SPRITE_SIZE,                                                               \
            .height = (f32)(sprite)->height / SPRITE_SIZE,                                                             \
            .shape = PhysicsColliderShape##shape_,                                                                     \
            .allowCollision = true,                                                                                    \
        };                                                                                                             \
        CreatePhysicsBody(&body, (x), (y), PhysicsBodyType##type, false, &desc, 1);                                    \
        ecs_set_ptr(g_world, PART_##id, PHYSICS_BODY, &body);                                                          \
        ecs_add(g_world, PART_##id, LEVEL);                                                                            \
    }

    PART(ground, &s_ground, -8.0f, -10.0f, 0.0f, Static, Rect);
    PART(ground2, &s_ground, 8.0f, -10.0f, 0.0f, Static, Rect);

    g_player = CreatePlayer(0.0f, 0.0f);

#undef PART
}
