#pragma once

#include "game/game.h"
#include "game/image.h"

typedef struct SPRITE
{
    PSPRITE_SHEET sheet;
    u16 xOffset;
    u16 yOffset;
    u16 width;
    u16 height;
} SPRITE, *PSPRITE;
extern ECS_COMPONENT_DECLARE(SPRITE);
