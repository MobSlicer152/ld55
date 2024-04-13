#include "game.h"

#include "globals.h"
#include "log.h"
#include "sprites.h"
#include "image.h"
#include "util.h"

#include "components.h"

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

    RegisterComponents();

    InitializeWindowSystem();
    InitializeRenderSystem();
    InitializePhysicsSystem();

    LoadQoiImage("sprites.qoi", &g_spriteSheet);

    f32 last;
    f32 now;
    f32 delta;

    g_player = ecs_new_entity(g_world, "player");
    ecs_set_ptr(g_world, g_player, SPRITE, &s_player);
    PHYSICS_BODY body = {nvBody_new(nvBodyType_DYNAMIC, nvRectShape_new(s_player.width, s_player.height), NV_VEC2(0.0f, 0.0f), 0.0f, nvMaterial_BASIC)};
    nvSpace_add(g_space, body.body);
    ecs_set_ptr(g_world, g_player, PHYSICS_BODY, &body);

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
