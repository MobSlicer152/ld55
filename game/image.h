#pragma once

#include "game.h"

typedef struct IMAGE
{
    SDL_Texture *texture;
    u32 width;
    u32 height;
} IMAGE, *PIMAGE;

typedef struct SPRITE
{
    PIMAGE sheet;
    u16 xOffset;
    u16 yOffset;
    u16 width;
    u16 height;
} SPRITE, * PSPRITE;

extern void LoadQoiImage(cstr path, PIMAGE image);
extern void FreeQoiImage(PIMAGE image);