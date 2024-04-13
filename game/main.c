#include "game.h"

#include "components.h"
#include "image.h"
#include "log.h"
#include "util.h"

#include "globals/misc.h"
#include "globals/prefabs.h"
#include "globals/sprites.h"

#include "systems/discord.h"
#include "systems/input.h"
#include "systems/physics.h"
#include "systems/render.h"
#include "systems/window.h"

s32 main(s32 argc, char *argv[])
{
#ifdef GAME_DEBUG
    LogSetLevel(LogLevelDebug);
#endif

    OpenStorage();

    ecs_os_set_api_defaults();
    ecs_os_api_t osApi = ecs_os_api;
    osApi.log_ = EcsLog;
    osApi.malloc_ = EcsMalloc;
    osApi.calloc_ = EcsCalloc;
    osApi.realloc_ = EcsRealloc;
    osApi.free_ = EcsFree;
    ecs_os_set_api(&osApi);

    LogInfo("Creating world");
    g_world = ecs_init_w_args(argc, argv);

#ifdef GAME_DEBUG
    ECS_IMPORT(g_world, FlecsMonitor);
    ecs_singleton_set(g_world, EcsRest, {0});
#endif

    RegisterComponents();

    InitializeWindowSystem();
    InitializeRenderSystem();
    InitializePhysicsSystem();
    InitializeInputSystem();
    InitializeDiscordSystem();

    LoadQoiImage("sprites.qoi", &g_spriteSheet);

    g_player = CreatePlayer();

    CreateLevel();

    f32 last;
    f32 now;
    f32 delta;

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
