#pragma once

#include "game.h"

typedef struct SPRITE_SHEET
{
    SDL_Texture *texture;
    u32 width;
    u32 height;
} SPRITE_SHEET, *PSPRITE_SHEET;

extern bool LoadSpriteSheet(cstr path, PSPRITE_SHEET spriteSheet);
extern void FreeSpriteSheet(PSPRITE_SHEET spriteSheet);
