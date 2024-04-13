#pragma once

#include "game.h"

#include "util.h"

BEGIN_EXTERN_C

MAKECOMPONENT(TRANSFORM,
{
    f32 x;
    f32 y;
    f32 zRotation;
    f32 xScale;
    f32 yScale;
})

MAKECOMPONENT(PHYSICS_BODY,
{
    void *body;
    f32 xSpeed;
    f32 ySpeed;
    TRANSFORM transform;
    enum PHYSICS_BODY_TYPE type;
})

extern ECS_TAG_DECLARE(PLAYER);

extern ECS_TAG_DECLARE(LEVEL);

extern void RegisterComponents(void);

END_EXTERN_C
