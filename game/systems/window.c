#include "game/globals.h"
#include "game/log.h"

#include "window.h"

static void WindowUpdate(ecs_iter_t *iter)
{
    (void)iter;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_WINDOW_RESIZED:
            LogInfo("Window resized from to %ux%u", event.window.data1, event.window.data2);
            break;
        case SDL_EVENT_QUIT:
            LogInfo("Quit requested");
            g_running = false;
            break;
        }
    }
}

static void WindowDestroy(void)
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
}

void InitializeWindowSystem(void)
{
    LogInfo("Initializing window system");

    g_window = SDL_CreateWindow(GAME_NAME, 1024, 768, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);
    if (!g_window)
    {
        Error("failed to create window: %s", SDL_GetError());
    }

    g_renderer = SDL_CreateRenderer(g_window, NULL, SDL_RENDERER_ACCELERATED);
    if (!g_renderer)
    {
        Error("failed to create renderer: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(g_renderer, GAME_WIDTH, GAME_HEIGHT, SDL_LOGICAL_PRESENTATION_STRETCH, SDL_SCALEMODE_NEAREST);

    ECS_SYSTEM(g_world, WindowUpdate, EcsPreUpdate);

    ecs_atfini(g_world, (ecs_fini_action_t)WindowDestroy, NULL);
}
