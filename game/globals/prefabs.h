#pragma once

#include "game/game.h"

#include "game/components.h"

BEGIN_EXTERN_C

extern ecs_entity_t CreatePlayer(f32 x, f32 y);
extern ecs_entity_t CreateProjectile(ecs_entity_t owner, PROJECTILE_TYPE type, f32 targetX, f32 targetY);

extern void CreateLevel(void);

END_EXTERN_C
