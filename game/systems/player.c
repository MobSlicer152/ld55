#include "game/log.h"
#include "game/util.h"

#include "game/globals/misc.h"

#include "input.h"
#include "physics.h"
#include "player.h"

static void HandlePlayerInput(ecs_iter_t *iter)
{
    PCPHYSICS_BODY body = ecs_get(g_world, g_player, PHYSICS_BODY);

    f32 xForce = 0.0f;
    f32 yForce = 0.0f;

    if (body->xSpeed > -PLAYER_RUN_SPEED && g_input.keyboard[KEY_LEFT])
    {
        xForce -= PLAYER_RUN_FORCE;
    }
    if (body->xSpeed < PLAYER_RUN_SPEED && g_input.keyboard[KEY_RIGHT])
    {
        xForce += PLAYER_RUN_FORCE;
    }

    if (g_input.keyboard[KEY_DASH])
    {
        xForce *= PLAYER_DASH_FACTOR;
    }

    if (g_input.keyboard[KEY_JUMP] || g_input.keyboard[KEY_JUMP_ALT])
    {
        yForce += PLAYER_JUMP_FORCE;
    }

    ApplyForceToPhysicsBody(body, xForce, yForce);
}

void InitializePlayerSystem(void)
{
    LogInfo("Initializing player system");

    ECS_SYSTEM_EX(g_world, HandlePlayerInput, EcsOnUpdate, false, PHYSICS_INTERVAL);
}
