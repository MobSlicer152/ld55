#include "game/globals.h"
#include "game/log.h"
#include "game/util.h"

#include "physics.h"

static void PhysicsUpdate(ecs_iter_t *iter)
{
    nvSpace_step(g_space, iter->delta_system_time, 5, 5, 5, 1);
}

static void Shutdown(void)
{
    nvSpace_free(g_space);
}

void InitializePhysicsSystem(void)
{
    LogInfo("Initializing physics system");

    g_space = nvSpace_new();

    ECS_SYSTEM_EX(g_world, PhysicsUpdate, EcsOnUpdate, true, PHYSICS_INTERVAL);

    ecs_atfini(g_world, (ecs_fini_action_t)Shutdown, NULL);
}