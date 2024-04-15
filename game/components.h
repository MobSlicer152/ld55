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

MAKECOMPONENT(struct, POSITION, {
    f32 x;
    f32 y;
})

MAKECOMPONENT(struct, ROTATION, { f32 value; });

MAKECOMPONENT(struct, PHYSICS_BODY, {
    void *body;
    f32 xSpeed;
    f32 ySpeed;
    enum PHYSICS_BODY_TYPE type;
})

MAKECOMPONENT(struct, HEALTH, { f32 value; })

MAKECOMPONENT(struct, BURN, {
    f32 damage;
    f32 remainingTime;
})

MAKECOMPONENT(struct, JUMP_COOLDOWN, { f32 value; })

MAKECOMPONENT(struct, FLIP, { bool value; })

MAKECOMPONENT(enum, PROJECTILE_TYPE,
              {ProjectileTypeFireball, ProjectileTypeSaw, ProjectileTypeEnergyBolt, ProjectileTypeCount})
MAKETAG(enum, PROJECTILE_HIT_EFFECT, {ProjectileHitEffectNone, ProjectileHitEffectExplode, ProjectileHitEffectBurn})
MAKECOMPONENT(struct, PROJECTILE_MAX_HITS, { u8 value; })
MAKECOMPONENT(struct, PROJECTILE_COOLDOWN, { f32 value; })
MAKECOMPONENT(struct, PLAYER, {
    PROJECTILE_TYPE activeProjectileType;
    f32 projectileSwitchCooldown;
})

extern ECS_TAG_DECLARE(LEVEL);

extern void RegisterComponents(void);

END_EXTERN_C
