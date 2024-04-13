#include "game/log.h"
#include "game/util.h"

#include "game/globals/misc.h"

#include "input.h"
#include "physics.h"
#include "player.h"

static void HandlePlayerInput(ecs_iter_t *iter)
{
    PCPHYSICS_BODY body = ecs_get(g_world, g_player, PHYSICS_BODY);

    f32 xSpeed = 0.0f;
    f32 ySpeed = 0.0f;
    GetPhysicsBodyVelocity(body, &xSpeed, &ySpeed);
    
    f32 targetXSpeed = g_input.xAxis * PLAYER_RUN_SPEED;
    f32 yImpulse = g_input.yAxis * PLAYER_JUMP_SPEED;

    xSpeed = Lerp(xSpeed, targetXSpeed, iter->delta_system_time);

    SetPhysicsBodyVelocity(body, xSpeed, ySpeed);
    ApplyForceToPhysicsBody(body, 0.0f, yImpulse);
}

void InitializePlayerSystem(void)
{
    LogInfo("Initializing player system");

    ECS_SYSTEM_EX(g_world, HandlePlayerInput, EcsOnUpdate, false, PHYSICS_INTERVAL);
}
