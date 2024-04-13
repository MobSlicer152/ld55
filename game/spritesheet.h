#pragma once

#include "game.h"

typedef struct SPRITE_SHEET
{
    SDL_Texture *texture;
    u32 width;
    u32 height;
} SPRITE_SHEET, *PSPRITE_SHEET;

typedef struct SPRITE
{
    PSPRITE_SHEET sheet;
    u16 xOffset;
    u16 yOffset;
    u16 width;
    u16 height;
} SPRITE, * PSPRITE;

extern void LoadSpriteSheet(cstr path, PSPRITE_SHEET spriteSheet);
extern void FreeSpriteSheet(PSPRITE_SHEET spriteSheet);
