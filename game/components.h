#pragma once

#include "game.h"

BEGIN_EXTERN_C

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
    void *body;
    TRANSFORM transform;
    enum PHYSICS_BODY_TYPE type;
} PHYSICS_BODY, *PPHYSICS_BODY;
extern ECS_COMPONENT_DECLARE(PHYSICS_BODY);

extern ECS_COMPONENT_DECLARE(SPRITE);

extern ECS_TAG_DECLARE(PLAYER);

extern ECS_TAG_DECLARE(LEVEL);

extern void RegisterComponents(void);

END_EXTERN_C
