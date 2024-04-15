#include "game/components.h"
#include "game/log.h"

#include "game/globals/misc.h"

#include "cooldown.h"

static void TickProjectileCooldown(ecs_iter_t *iter)
{
    PPROJECTILE_COOLDOWN cooldowns = ecs_field(iter, PROJECTILE_COOLDOWN, 1);

    for (s32 i = 0; i < iter->count; i++)
    {
        cooldowns[i].value -= iter->delta_system_time;
    }
}

void InitializeCooldownSystem(void)
{
    LogInfo("Initializing cooldown system");

    ECS_SYSTEM(g_world, TickProjectileCooldown, EcsOnUpdate, PROJECTILE_COOLDOWN);
}
