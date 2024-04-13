#pragma once

#include "game/game.h"

BEGIN_EXTERN_C

extern ecs_entity_t CreatePlayer(f32 x, f32 y);

extern void CreateLevel(void);

END_EXTERN_C
