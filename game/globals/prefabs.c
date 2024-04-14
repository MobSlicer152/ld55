#include "game/components.h"

#include "game/systems/physics.h"
#include "game/systems/player.h"

#include "misc.h"
#include "prefabs.h"
#include "sprites.h"

ecs_entity_t CreatePlayer(f32 x, f32 y)
{
    ecs_entity_t entity = ecs_new_entity(g_world, "player");

    ecs_set(g_world, entity, ANIMATION, {&s_player, 1});

    PHYSICS_BODY body = {0};

    PHYSICS_COLLIDER_DESC mainCollider = {.x = 0.0f,
                                          .y = 0.0f,
                                          .width = s_player.width,
                                          .height = s_player.height,
                                          .mass = PLAYER_MASS,
                                          .shape = PhysicsColliderShapeRect,
                                          .allowCollision = true};

    PHYSICS_COLLIDER_DESC colliders[] = {mainCollider};

    CreatePhysicsBody(&body, x, y, PhysicsBodyTypeDynamic, false, colliders, ARRAYSIZE(colliders));

    ecs_set_ptr(g_world, entity, PHYSICS_BODY, &body);
    ecs_add(g_world, entity, FLIP);

    PLAYER playerData = {0};
    ecs_set_ptr(g_world, entity, PLAYER, &playerData);

    return entity;
}


static const f32 projectileDamage[ProjectileTypeCount] = {
    10.0f, // fireball
    30.0f, // saw
    50.0f, // energy
};
static const f32 projectileCooldown[ProjectileTypeCount] = {
    0.2f, // fireball
    0.7f, // saw
    2.0f, // energy
};
static const f32 projectileSpeed[ProjectileTypeCount] = {
    20.0f, // fireball
    50.0f, // saw
    103.0f, // energy bolt
};
static const f32 projectileMass[ProjectileTypeCount] = {
    0.03f, // fireball
    4.5f, // saw, pi * (0.5m) ^ 2 * 0.002 m * 7700 kg/m^3 ~= 4.5 kg
    0.01f, // energy bolt (assuming it's hydrogen plasma)
};
static const f32 projectileRestitution[ProjectileTypeCount] = {
    0.0f, // fireballs don't bounce
    0.7f, // saws bounce
    0.0f // energy bolt also don't bounce
};


ecs_entity_t CreateProjectile(ecs_entity_t owner, PROJECTILE_TYPE type, f32 targetX, f32 targetY)
{
    PCSPRITE sprite = &s_projectiles[type];
    f32 damage = projectileDamage[type];
    f32 cooldown = projectileCooldown[type];
    f32 speed = projectileSpeed[type];
    f32 mass = projectileMass[type];


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
            .width = (sprite)->width,                                                                                  \
            .height = (sprite)->height,                                                                                \
            .shape = PhysicsColliderShape##shape_,                                                                     \
            .allowCollision = true,                                                                                    \
        };                                                                                                             \
        CreatePhysicsBody(&body, (x), (y), PhysicsBodyType##type, false, &desc, 1);                                    \
        ecs_set_ptr(g_world, PART_##id, PHYSICS_BODY, &body);                                                          \
        ecs_add(g_world, PART_##id, LEVEL);                                                                            \
    }

    PART(ground, &s_ground, -8.0f, -7.5f, 0.0f, Static, Rect);
    PART(ground2, &s_ground, 8.0f, -7.5f, 0.0f, Static, Rect);
    PART(wall, &s_wall, 16.5f, 0.0f, 0.0f, Static, Rect);
    PART(wall2, &s_wall, -16.5f, 0.0f, 0.0f, Static, Rect);

    g_player = CreatePlayer(0.0f, 0.0f);

#undef PART
}
