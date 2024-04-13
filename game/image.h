#pragma once

#include "game.h"

#include "util.h"

BEGIN_EXTERN_C

typedef struct IMAGE
{
    SDL_Texture *texture;
    u32 width;
    u32 height;
} IMAGE, *PIMAGE;

MAKECOMPONENT(SPRITE, 
{
    PIMAGE sheet;
    u16 xOffset;
    u16 yOffset;
    u16 width;
    u16 height;
})

extern void LoadQoiImage(cstr path, PIMAGE image);
extern void FreeQoiImage(PIMAGE image);

END_EXTERN_C
