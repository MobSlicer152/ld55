#pragma once

#include "game/game.h"

#include "game/util.h"

BEGIN_EXTERN_C

MAKETAG(struct, INPUT_STATE, {
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

#define MAKE_KEY(scancode) (g_input.keyboard[(scancode)])
#define INPUT_LEFT MAKE_KEY(SDL_SCANCODE_A)
#define INPUT_RIGHT MAKE_KEY(SDL_SCANCODE_D)
#define INPUT_JUMP MAKE_KEY(SDL_SCANCODE_SPACE)
#define INPUT_JUMP_ALT MAKE_KEY(SDL_SCANCODE_W)
#define INPUT_DASH MAKE_KEY(SDL_SCANCODE_LSHIFT)
#define INPUT_CROUCH MAKE_KEY(SDL_SCANCODE_LCTRL)
#define INPUT_CROUCH_ALT MAKE_KEY(SDL_SCANCODE_S)
#define INPUT_SUMMON MAKE_KEY(SDL_SCANCODE_V)
#define INPUT_SWITCH_PROJECTILE MAKE_KEY(SDL_SCANCODE_R)
#define INPUT_QUIT MAKE_KEY(SDL_SCANCODE_ESC);

extern void InitializeInputSystem(void);
extern void MouseWorldPosition(f32 *x, f32 *y);

END_EXTERN_C
