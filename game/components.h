#pragma once

#include "game.h"

#include "image.h"
#include "util.h"

BEGIN_EXTERN_C

MAKECOMPONENT(struct, ANIMATION, {
    PCANIMATED_SPRITE frames;
    u32 minFrame;
    u32 maxFrame;
    u32 currentFrame;
    bool paused;
    f32 timeSinceLastFrame;
})

MAKECOMPONENT(struct, TRANSFORM, {
    f32 x;
    f32 y;
    f32 zRotation;
    f32 xScale;
    f32 yScale;
})

MAKECOMPONENT(struct, PHYSICS_BODY, {
    void *body;
    f32 xSpeed;
    f32 ySpeed;
    TRANSFORM transform;
    enum PHYSICS_BODY_TYPE type;
})

MAKECOMPONENT(struct, HEALTH, {
    f32 value;
})

MAKECOMPONENT(struct, BURN, {
    f32 damage;
    f32 remainingTime;
})

MAKECOMPONENT(struct, JUMP_COOLDOWN, {
    f32 value;
})

MAKECOMPONENT(struct, FLIP, {
    bool value;
})

MAKECOMPONENT(enum, PROJECTILE_TYPE, {ProjectileTypeFireball, ProjectileTypeSaw, ProjectileTypeEnergyBolt, ProjectileTypeCount})
MAKETAG(enum, PROJECTILE_HIT_EFFECT, {ProjectileHitEffectNone, ProjectileHitEffectExplode, ProjectilHitEffectBurn})
MAKECOMPONENT(struct, PLAYER, {
    PROJECTILE_TYPE activeProjectileType;
    f32 projectileSwitchCooldown;
    f32 projectileCooldown;
})

extern ECS_TAG_DECLARE(LEVEL);

extern void RegisterComponents(void);

END_EXTERN_C
