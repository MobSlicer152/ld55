#include "game/components.h"
#include "game/log.h"
#include "game/image.h"

#include "game/globals/misc.h"

#include "render.h"

static void RenderBegin(ecs_iter_t *iter)
{
    SDL_SetRenderDrawColor(g_renderer, 0, 0xAA, 0xFF, 0);
    SDL_RenderClear(g_renderer);
}

static void DrawSprite(PSPRITE sprite, PTRANSFORM transform)
{
    SDL_FRect srcRect = {sprite->xOffset, sprite->yOffset, sprite->width, sprite->height};
    SDL_FRect destRect = {transform->x, transform->y, transform->xScale * sprite->width, transform->yScale * sprite->height};

    SDL_RenderTextureRotated(g_renderer, sprite->sheet->texture, &srcRect, &destRect, transform->zRotation, NULL, SDL_FLIP_NONE);
}

static void RenderDrawStaticSprite(ecs_iter_t *iter)
{
    PSPRITE sprites = ecs_field(iter, SPRITE, 1);
    PTRANSFORM transforms = ecs_field(iter, TRANSFORM, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        DrawSprite(&sprites[i], &transforms[i]);
    }
}

static void RenderDrawDynamicSprite(ecs_iter_t *iter)
{
    PSPRITE sprites = ecs_field(iter, SPRITE, 1);
    PPHYSICS_BODY bodies = ecs_field(iter, PHYSICS_BODY, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        DrawSprite(&sprites[i], &(TRANSFORM){bodies[i].body->position.x, bodies[i].body->position.y, bodies[i].body->angle, 1.0f, 1.0f});
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
    ECS_SYSTEM(g_world, RenderDrawStaticSprite, EcsPostUpdate, SPRITE, TRANSFORM);
    ECS_SYSTEM(g_world, RenderDrawDynamicSprite, EcsPostUpdate, SPRITE, PHYSICS_BODY);
    ECS_SYSTEM(g_world, RenderEnd, EcsPostFrame);
}
