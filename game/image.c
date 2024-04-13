#define QOI_IMPLEMENTATION

#include "globals/misc.h"

#include "image.h"
#include "util.h"

void LoadQoiImage(cstr path, PIMAGE image)
{
    u64 size = 0;
    void *data = Read(path, &size);

    qoi_desc desc = {0};
    void *imageData = qoi_decode(data, size, &desc, 4);
    if (!data)
    {
        Error("failed to read image %s", path);
    }

    FREE(data);

    if (desc.channels != 4 || desc.colorspace != QOI_SRGB)
    {
        Error("can't handle image %s", path);
    }

    image->width = desc.width;
    image->height = desc.height;
    image->texture =
        SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, image->width, image->height);
    if (!image->texture)
    {
        Error("failed to create %ux%u texture", image->width, image->height);
    }

    SDL_UpdateTexture(image->texture, NULL, imageData, image->width * 4);
    SDL_SetTextureScaleMode(image->texture, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(image->texture, SDL_BLENDMODE_BLEND);

    FREE(imageData);
}

void DestroyQoiImage(PIMAGE image)
{
    SDL_DestroyTexture(image->texture);
}
