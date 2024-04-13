#include "game.h"

#include "globals.h"
#include "log.h"
#include "sprites.h"
#include "spritesheet.h"
#include "util.h"

#include "components/sprite.h"

#include "systems/render.h"
#include "systems/window.h"

s32 main(s32 argc, char* argv[])
{
    OpenStorage();

    LogInfo("Creating world");
    g_world = ecs_init();

    InitializeWindowSystem();
    InitializeRenderSystem();

    LoadSpriteSheet("assets/sprites.qoi", &g_spriteSheet);

    f32 last;
    f32 now;
    f32 delta;

    g_player = ecs_new_entity(g_world, "player");
    ecs_add(g_world, g_player, SPRITE);
    ecs_set_ptr(g_world, g_player, SPRITE, &s_player);

    g_running = true;
    last = SDL_GetTicks() / 1000.0f;
    while (g_running)
    {
        now = SDL_GetTicks() / 1000.0f;
        delta = now - last;

        ecs_progress(g_world, delta);

        last = now;
    }

    LogInfo("Destroying world");
    ecs_fini(g_world);
}
