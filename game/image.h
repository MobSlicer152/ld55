#pragma once

#include "game.h"

#include "util.h"

BEGIN_EXTERN_C

MAKETAG(struct, IMAGE, {
    SDL_Texture *texture;
    u32 width;
    u32 height;
})

MAKETAG(struct, SPRITE_OFFSET, {
    f32 x;
    f32 y;
})

MAKECOMPONENT(struct, SPRITE, {
    PIMAGE sheet;
    SPRITE_OFFSET offset;
    f32 width;
    f32 height;
})

MAKETAG(struct, ANIMATED_SPRITE, {
    PIMAGE sheet;
    f32 frameTime;
    u32 frameCount;
    PCSPRITE_OFFSET frames;
    f32 width;
    f32 height;
})

extern void LoadQoiImage(cstr path, PIMAGE image);
extern void FreeQoiImage(PIMAGE image);

END_EXTERN_C
