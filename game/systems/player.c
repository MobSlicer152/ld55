#include "game/components.h"
#include "game/log.h"
#include "game/util.h"

#include "game/globals/misc.h"

#include "input.h"
#include "physics.h"
#include "player.h"

static void HandlePlayerCooldowns(ecs_iter_t *iter)
{
    PPLAYER player = ecs_get_mut(g_world, g_player, PLAYER);
    
    if (player->projectileSwitchCooldown > 0.0f)
    {
        player->projectileSwitchCooldown -= iter->delta_system_time;
    }
    
    if (player->projectileCooldown > 0.0f)
    {
        player->projectileCooldown -= iter->delta_system_time;
    }
}

static void HandlePlayerInput(ecs_iter_t *iter)
{
    PCPHYSICS_BODY body = ecs_get(g_world, g_player, PHYSICS_BODY);
    PPLAYER player = ecs_get_mut(g_world, g_player, PLAYER);
    PFLIP flip = ecs_get_mut(g_world, g_player, FLIP);
    PANIMATION animation = ecs_get_mut(g_world, g_player, ANIMATION);

    f32 xSpeed = 0.0f;
    f32 ySpeed = 0.0f;
    GetPhysicsBodyVelocity(body, &xSpeed, &ySpeed);

    f32 targetXSpeed = g_input.xAxis * PLAYER_RUN_SPEED;
    f32 yImpulse = g_input.yAxis * PLAYER_JUMP_FORCE;

    xSpeed = Lerp(xSpeed, targetXSpeed, iter->delta_system_time);

    flip->value = targetXSpeed < 0.0f;

    if (fabs(body->xSpeed) < 0.001)
    {
        animation->minFrame = 0;
        animation->maxFrame = 0;
    }
    else
    {
        animation->minFrame = 1;
        animation->maxFrame = 3;
    }

    if (player->projectileSwitchCooldown < 0.0f && INPUT_SWITCH_PROJECTILE)
    {
        WRAPPED_INCREMENT(player->activeProjectileType, 0, ProjectileTypeCount);
    }

    SetPhysicsBodyVelocity(body, xSpeed, ySpeed);
    ApplyForceToPhysicsBody(body, 0.0f, yImpulse);
}

void InitializePlayerSystem(void)
{
    LogInfo("Initializing player system");

    ECS_SYSTEM(g_world, HandlePlayerCooldowns, EcsOnUpdate);
    ECS_SYSTEM_EX(g_world, HandlePlayerInput, EcsOnUpdate, false, PHYSICS_INTERVAL);
}
