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

    PHYSICS_COLLIDER_DESC mainCollider = {.width = s_player.width,
                                          .height = s_player.height,
                                          .mass = PLAYER_MASS,
                                          .shape = PhysicsColliderShapeRect,
                                          .allowCollision = true};

    PHYSICS_COLLIDER_DESC colliders[] = {mainCollider};

    PPHYSICS_BODY body = ecs_emplace(g_world, entity, PHYSICS_BODY);
    CreatePhysicsBody(body, x, y, PhysicsBodyTypeDynamic, false, colliders, ARRAYSIZE(colliders));

    ecs_add(g_world, entity, FLIP);
    ecs_add(g_world, entity, POSITION);
    ecs_set(g_world, entity, PROJECTILE_COOLDOWN, {0.0f});

    PPLAYER player = ecs_emplace(g_world, entity, PLAYER);
    memset(player, 0, sizeof(PLAYER));

    return entity;
}

static const f32 projectileDamage[ProjectileTypeCount] = {
    10.0f, // fireball
    30.0f, // saw
    50.0f, // energy
};
static const f32 projectileCooldown[ProjectileTypeCount] = {
    0.4f, // fireball
    0.7f, // saw
    2.0f, // energy
};
static const f32 projectileSpeed[ProjectileTypeCount] = {
    20.0f,  // fireball
    50.0f,  // saw
    103.0f, // energy bolt
};
static const f32 projectileMass[ProjectileTypeCount] = {
    0.03f, // fireball
    4.5f,  // saw, pi * (0.5m / 2) ^ 2 * 0.002 m * 7700 kg/m^3 ~= 4.5 kg
    0.01f, // energy bolt (assuming it's hydrogen plasma)
};
static const f32 projectileRestitution[ProjectileTypeCount] = {
    0.0f, // fireballs don't bounce
    0.7f, // saws bounce
    0.0f  // energy bolt also don't bounce
};
static const PROJECTILE_HIT_EFFECT projectileHitEffect[ProjectileTypeCount] = {
    ProjectileHitEffectBurn,    // fireball
    ProjectileHitEffectNone,    // saw
    ProjectileHitEffectExplode, // energy bolt
};
static const PROJECTILE_MAX_HITS projectileMaxHits[ProjectileTypeCount] = {
    1, // fireball
    5, // saw,
    1, // energy bolt
};

ecs_entity_t CreateProjectile(ecs_entity_t owner, PROJECTILE_TYPE type, f32 targetX, f32 targetY)
{
    PCSPRITE sprite = &s_projectiles[type];
    f32 damage = projectileDamage[type];
    f32 cooldown = projectileCooldown[type];
    f32 speed = projectileSpeed[type];
    f32 mass = projectileMass[type];
    f32 restitution = projectileRestitution[type];
    PROJECTILE_HIT_EFFECT hitEffect = projectileHitEffect[type];

    PCPOSITION ownerPosition = ecs_get(g_world, owner, POSITION);
    PCFLIP ownerFlip = ecs_get(g_world, owner, FLIP);
    PPROJECTILE_COOLDOWN projectileCooldown = ecs_get_mut(g_world, owner, PROJECTILE_COOLDOWN);

    f32 x = ownerPosition->x + 0.5f * copysignf(1.0f, targetX);
    f32 y = ownerPosition->y;

    ecs_entity_t projectile = ecs_new_w_pair(g_world, EcsChildOf, owner);
    ecs_set_ptr(g_world, projectile, SPRITE, sprite);
    ecs_add(g_world, projectile, POSITION);
    ecs_add(g_world, projectile, ROTATION);
    PPHYSICS_BODY body = ecs_emplace(g_world, projectile, PHYSICS_BODY);
    PHYSICS_COLLIDER_DESC collider = {
        .width = s_projectiles[type].width,
        .height = s_projectiles[type].height,
        .mass = mass,
        .restitution = restitution,
    };
    CreatePhysicsBody(body, x, y, PhysicsBodyTypeDynamic, false, &collider, 1);

    Normalize(&targetX, &targetY);
    f32 xSpeed = targetX * speed;
    f32 ySpeed = targetY * speed;
    SetPhysicsBodyVelocity(body, xSpeed, ySpeed);

    projectileCooldown->value = cooldown;

    return projectile;
}

void CreateLevel(void)
{
#define PART(id, sprite, x, y, rotation, type, shape_)                                                                 \
    {                                                                                                                  \
        ecs_entity_t PART_##id = ecs_new_entity(g_world, #id);                                                         \
        ecs_set_ptr(g_world, PART_##id, SPRITE, (sprite));                                                             \
        PHYSICS_COLLIDER_DESC desc = {                                                                                 \
            .zRotation = (rotation),                                                                                   \
            .width = (sprite)->width,                                                                                  \
            .height = (sprite)->height,                                                                                \
            .shape = PhysicsColliderShape##shape_,                                                                     \
            .allowCollision = true,                                                                                    \
        };                                                                                                             \
        PPHYSICS_BODY body = ecs_emplace(g_world, PART_##id, PHYSICS_BODY);                                            \
        CreatePhysicsBody(body, (x), (y), PhysicsBodyType##type, false, &desc, 1);                                     \
        ecs_set_ptr(g_world, PART_##id, PHYSICS_BODY, &body);                                                          \
        ecs_set(g_world, PART_##id, POSITION, {(x), (y)});                                                             \
        ecs_add(g_world, PART_##id, LEVEL);                                                                            \
    }

    PART(ground, &s_ground, -8.0f, -7.5f, 0.0f, Static, Rect);
    PART(ground2, &s_ground, 8.0f, -7.5f, 0.0f, Static, Rect);
    PART(wall, &s_wall, 16.5f, 0.0f, 0.0f, Static, Rect);
    PART(wall2, &s_wall, -16.5f, 0.0f, 0.0f, Static, Rect);

    g_player = CreatePlayer(0.0f, 0.0f);

#undef PART
}
