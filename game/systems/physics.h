#pragma once

#include "game/game.h"

#include "game/components.h"

BEGIN_EXTERN_C

#define PHYSICS_INTERVAL (1.0 / 60.0)

typedef enum PHYSICS_BODY_TYPE
{
    PhysicsBodyTypeStatic = 0,
    PhysicsBodyTypeKinematic,
    PhysicsBodyTypeDynamic,
} PHYSICS_BODY_TYPE, *PPHYSICS_BODY_TYPE;

extern void InitializePhysicsSystem(void);
extern void CreatePhysicsBody(PPHYSICS_BODY body, f32 x, f32 y, f32 zRotation, f32 width, f32 height,
                              PHYSICS_BODY_TYPE type, f32 mass, bool fixedRotation);
extern void ApplyForceToPhysicsBody(PCPHYSICS_BODY body, f32 xForce, f32 yForce);
extern void GetPhysicsBodyVelocity(PCPHYSICS_BODY body, f32 *x, f32 *y);
extern void SetPhysicsBodyVelocity(PCPHYSICS_BODY body, f32 x, f32 y);

END_EXTERN_C
