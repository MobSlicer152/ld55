#pragma once

#include "game/game.h"

#include "game/util.h"

BEGIN_EXTERN_C

MAKETAG(struct, INPUT_STATE,
{
    const u8 *keyboard;

    f32 xAxis;
    f32 yAxis;

    bool leftClick;
    bool middleClick;
    bool rightClick;
    f32 scroll;
    f32 mouseX;
    f32 mouseY;
    f32 mouseDeltaX;
    f32 mouseDeltaY;
})

extern void InitializeInputSystem(void);

END_EXTERN_C
