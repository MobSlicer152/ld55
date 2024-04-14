#pragma once

#include "game/game.h"

BEGIN_EXTERN_C

#define PLAYER_MAX_HEALTH (100.0f)
#define PLAYER_MASS (80.0f)
#define PLAYER_RUN_SPEED (10.0f)
#define PLAYER_DASH_FACTOR (2.0f)
#define PLAYER_JUMP_SPEED (5.0f)
#define PLAYER_JUMP_FORCE (PLAYER_MASS * PLAYER_JUMP_SPEED)
#define PLAYER_PROJECTILE_SWITCH_COOLDOWN (1.0f)

extern void InitializePlayerSystem(void);

END_EXTERN_C
