#include "game/globals.h"
#include "game/log.h"

#include "game/components/sprite.h"

#include "render.h"

static void RenderBegin(ecs_iter_t *iter)
{
    SDL_SetRenderDrawColor(g_renderer, 0, 0xAA, 0xFF, 0);
    SDL_RenderClear(g_renderer);
}

static void DrawSprite(PSPRITE sprite)
{
    SDL_FRect srcRect = {sprite->xOffset, sprite->yOffset, sprite->width, sprite->height};
    SDL_FRect destRect = {0.0f, 0.0f, 0.0f, 0.0f};

    SDL_RenderTextureRotated(g_renderer, sprite->sheet->texture, &srcRect, &destRect, 0.0, NULL, SDL_FLIP_NONE);
}

static void RenderDrawSprite(ecs_iter_t *iter)
{
    PSPRITE Sprites = ecs_field(iter, SPRITE, 1);

    for (s32 i = 0; i < iter->count; i++)
    {
        DrawSprite(&Sprites[i]);
    }
}

static void RenderEnd(ecs_iter_t *iter)
{
    SDL_RenderPresent(g_renderer);
}

void InitializeRenderSystem(void)
{
    LogInfo("Initializing render system");

    ECS_SYSTEM(g_world, RenderBegin, EcsPreFrame);
    ECS_SYSTEM(g_world, RenderDrawSprite, EcsPostUpdate);
    ECS_SYSTEM(g_world, RenderEnd, EcsPostFrame);
}
