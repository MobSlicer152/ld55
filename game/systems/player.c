#include "game/components.h"
#include "game/log.h"
#include "game/util.h"

#include "game/globals/misc.h"
#include "game/globals/prefabs.h"

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
}

static void HandlePlayerInput(ecs_iter_t *iter)
{
    PCPHYSICS_BODY body = ecs_get(g_world, g_player, PHYSICS_BODY);
    PCPROJECTILE_COOLDOWN projectileCooldown = ecs_get(g_world, g_player, PROJECTILE_COOLDOWN);
    PPLAYER player = ecs_get_mut(g_world, g_player, PLAYER);
    PFLIP flip = ecs_get_mut(g_world, g_player, FLIP);
    PANIMATION animation = ecs_get_mut(g_world, g_player, ANIMATION);

    f32 xSpeed = 0.0f;
    f32 ySpeed = 0.0f;
    GetPhysicsBodyVelocity(body, &xSpeed, &ySpeed);

    f32 targetXSpeed = g_input.xAxis * PLAYER_RUN_SPEED;
    f32 yImpulse = g_input.yAxis * PLAYER_JUMP_FORCE;

    xSpeed = Lerp(xSpeed, targetXSpeed, iter->delta_system_time);

    flip->value = body->xSpeed < -FLT_EPSILON;

    if (fabs(body->xSpeed) < FLT_EPSILON)
    {
        animation->minFrame = 0;
        animation->maxFrame = 0;
    }
    else
    {
        animation->minFrame = 1;
        animation->maxFrame = 3;
    }

    if (projectileCooldown->value > 0.0f)
    {
        animation->minFrame += 2;
        animation->maxFrame += 2;
    }
    else if (INPUT_ATTACK)
    {
        CreateProjectile(g_player, player->activeProjectileType, g_input.mouseWorldX, g_input.mouseWorldY);
    }

    if (player->projectileSwitchCooldown < 0.0f && INPUT_SWITCH_PROJECTILE)
    {
        WRAPPED_INCREMENT(player->activeProjectileType, 0, ProjectileTypeCount);
        player->projectileSwitchCooldown = PLAYER_PROJECTILE_SWITCH_COOLDOWN;
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
