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
    f32 xOffset;
    f32 yOffset;
    f32 width;
    f32 height;
})

extern void LoadQoiImage(cstr path, PIMAGE image);
extern void FreeQoiImage(PIMAGE image);

END_EXTERN_C
