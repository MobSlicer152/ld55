#pragma once

#include "game/game.h"

typedef struct INPUT_STATE
{
    const u8 *keyboard;
    s32 keyboardSize;

    bool leftClick;
    bool middleClick;
    bool rightClick;
    f32 scroll;
    f32 mouseX;
    f32 mouseY;
    f32 mouseDeltaX;
    f32 mouseDeltaY;
} INPUT_STATE, *PINPUT_STATE;

extern void InitializeInputSystem(void);
