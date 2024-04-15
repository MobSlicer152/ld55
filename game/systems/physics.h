#pragma once

#include "game/game.h"

#include "game/components.h"
#include "game/util.h"

BEGIN_EXTERN_C

#define PHYSICS_INTERVAL (1.0 / 60.0)

MAKETAG(enum, PHYSICS_BODY_TYPE,
        {
            PhysicsBodyTypeStatic = 0,
            PhysicsBodyTypeKinematic,
            PhysicsBodyTypeDynamic,
        })

MAKETAG(enum, PHYSICS_COLLIDER_SHAPE, {PhysicsColliderShapeRect = 0, PhysicsColliderShapeCircle})

MAKETAG(struct, PHYSICS_COLLIDER_DESC, {
    PHYSICS_COLLIDER_SHAPE shape;

    f32 x;
    f32 y;
    f32 zRotation;

    f32 width;
    f32 height;

    f32 mass;
    f32 restitution;

    union {
        struct
        {
            u16 allowCollision : 1;
        };
        u16 flags;
    };
})

extern void InitializePhysicsSystem(void);
extern void CreatePhysicsBody(PPHYSICS_BODY body, f32 x, f32 y, PHYSICS_BODY_TYPE type, bool allowRotation,
                              PCPHYSICS_COLLIDER_DESC colliders, u32 colliderCount);
extern void ApplyForceToPhysicsBody(PCPHYSICS_BODY body, f32 xForce, f32 yForce);
extern void GetPhysicsBodyVelocity(PCPHYSICS_BODY body, f32 *x, f32 *y);
extern void SetPhysicsBodyVelocity(PCPHYSICS_BODY body, f32 x, f32 y);

END_EXTERN_C
