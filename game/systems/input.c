#include "game/log.h"

#include "game/globals/misc.h"

#include "input.h"

static void InputDebug(ecs_iter_t *iter)
{
    printf("\rleft %u middle %u right %u x %f y %f dx %f dy %f", g_input.leftClick, g_input.middleClick,
           g_input.rightClick, g_input.mouseX, g_input.mouseY, g_input.mouseDeltaX, g_input.mouseDeltaY);
}

static void InputUpdate(ecs_iter_t *iter)
{
    g_input.keyboard = SDL_GetKeyboardState(NULL);

    float oldX = g_input.mouseX;
    float oldY = g_input.mouseY;

    u32 mouseState = SDL_GetMouseState(&g_input.mouseX, &g_input.mouseY);

    g_input.leftClick = mouseState & SDL_BUTTON_LMASK;
    g_input.middleClick = mouseState & SDL_BUTTON_MMASK;
    g_input.rightClick = mouseState & SDL_BUTTON_RMASK;

    g_input.mouseDeltaX = g_input.mouseX - oldX;
    g_input.mouseDeltaY = g_input.mouseY - oldY;
}

extern void InitializeInputSystem(void)
{
    LogInfo("Initializing input system");

    SDL_SetRelativeMouseMode(true);

    ECS_SYSTEM(g_world, InputUpdate, EcsPreUpdate);
#ifdef GAME_DEBUG
    ECS_SYSTEM(g_world, InputDebug, EcsOnUpdate);
#endif
}
