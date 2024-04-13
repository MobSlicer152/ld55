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
            LogInfo("Window resized from %ux%u to %ux%u", g_width, g_height, event.window.data1, event.window.data2);
            g_width = event.window.data1;
            g_height = event.window.data2;
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

    g_width = 1024;
    g_height = 768;
    g_window = SDL_CreateWindow(GAME_NAME, g_width, g_height, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (!g_window)
    {
        Error("failed to create window: %s", SDL_GetError());
    }

    g_renderer = SDL_CreateRenderer(g_window, NULL, SDL_RENDERER_ACCELERATED);
    if (!g_renderer)
    {
        Error("failed to create renderer: %s", SDL_GetError());
    }

    ECS_SYSTEM(g_world, WindowUpdate, EcsPreUpdate);

    ecs_atfini(g_world, (ecs_fini_action_t)WindowDestroy, NULL);
}
