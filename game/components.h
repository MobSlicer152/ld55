#pragma once

#include "game.h"

typedef struct TRANSFORM
{
    f32 x;
    f32 y;
    f32 zRotation;
    f32 xScale;
    f32 yScale;
} TRANSFORM, *PTRANSFORM;
extern ECS_COMPONENT_DECLARE(TRANSFORM);

typedef struct PHYSICS_BODY
{
    nvBody *body;
} PHYSICS_BODY, *PPHYSICS_BODY;
extern ECS_COMPONENT_DECLARE(PHYSICS_BODY);

extern ECS_COMPONENT_DECLARE(SPRITE);

extern void RegisterComponents(void);
