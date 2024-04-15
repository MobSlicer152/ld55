#include "game/log.h"

#include "game/globals/misc.h"

#include "camera.h"
#include "input.h"

static void InputDebug(ecs_iter_t *iter)
{
    printf("\rleft %u middle %u right %u x %f y %f dx %f dy %f", g_input.leftClick, g_input.middleClick,
           g_input.rightClick, g_input.mouseX, g_input.mouseY, g_input.mouseDeltaX, g_input.mouseDeltaY);
}

static void MouseWorldPosition(f32 *x, f32 *y)
{
    // window -> world position
    *x = g_input.mouseX / g_width * GAME_WIDTH / SPRITE_SIZE + g_camera.x;
    *y = g_input.mouseY / g_height * GAME_HEIGHT / SPRITE_SIZE + g_camera.y;
    LogDebug("%f %f", *x, *y);
}

static void InputUpdate(ecs_iter_t *iter)
{
    g_input.keyboard = SDL_GetKeyboardState(NULL);

    g_input.xAxis = INPUT_LEFT ? -1.0f : 0.0f + INPUT_RIGHT ? 1.0f : 0.0f;
    g_input.yAxis = (INPUT_JUMP || INPUT_JUMP_ALT) ? 1.0f : 0.0f;

    float oldX = g_input.mouseX;
    float oldY = g_input.mouseY;

    u32 mouseState = SDL_GetMouseState(&g_input.mouseX, &g_input.mouseY);
    MouseWorldPosition(&g_input.mouseWorldX, &g_input.mouseWorldY);

    g_input.leftClick = mouseState & SDL_BUTTON_LMASK;
    g_input.middleClick = mouseState & SDL_BUTTON_MMASK;
    g_input.rightClick = mouseState & SDL_BUTTON_RMASK;

    g_input.mouseDeltaX = g_input.mouseX - oldX;
    g_input.mouseDeltaY = g_input.mouseY - oldY;

    if (INPUT_QUIT)
    {
        g_running = false;
    }
}

void InitializeInputSystem(void)
{
    LogInfo("Initializing input system");

    SDL_SetRelativeMouseMode(true);

    ECS_SYSTEM(g_world, InputUpdate, EcsPreUpdate);
#ifdef GAME_DEBUG
    // ECS_SYSTEM(g_world, InputDebug, EcsOnUpdate);
#endif
}
