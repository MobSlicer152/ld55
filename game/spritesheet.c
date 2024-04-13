#define QOI_IMPLEMENTATION

#include "globals.h"
#include "spritesheet.h"
#include "util.h"

void LoadSpriteSheet(cstr path, PSPRITE_SHEET spriteSheet)
{
    u64 size = 0;
    void *data = Read(path, &size);

    qoi_desc desc = {0};
    void *image = qoi_decode(data, size, &desc, 4);
    if (!data)
    {
        Error("failed to read image %s", path);
    }

    FREE(data);

    if (desc.channels != 4 || desc.colorspace != QOI_SRGB)
    {
        Error("can't handle image %s", path);
    }

    spriteSheet->width = desc.width;
    spriteSheet->height = desc.height;
    spriteSheet->texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, spriteSheet->width, spriteSheet->height);
    if (!spriteSheet->texture)
    {
        Error("failed to create %ux%u texture", spriteSheet->width, spriteSheet->height);
    }

    SDL_UpdateTexture(spriteSheet->texture, NULL, image, desc.width * desc.channels);
}
