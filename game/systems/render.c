#include "game/components.h"
#include "game/image.h"
#include "game/log.h"

#include "game/globals/misc.h"
#include "game/globals/sprites.h"

#include "input.h"
#include "render.h"

static void RenderBegin(ecs_iter_t *iter)
{
    SDL_SetRenderDrawColor(g_renderer, 0, 0xAA, 0xFF, 0);
    SDL_RenderClear(g_renderer);
}

static void DrawSprite(PCSPRITE sprite, PCTRANSFORM transform)
{
    SDL_FRect srcRect = {sprite->xOffset, sprite->yOffset, sprite->width, sprite->height};
    SDL_FRect destRect = {transform->x, transform->y, transform->xScale * sprite->width,
                          transform->yScale * sprite->height};

    SDL_RenderTextureRotated(g_renderer, sprite->sheet->texture, &srcRect, &destRect, transform->zRotation, NULL,
                             SDL_FLIP_NONE);
}

static void RenderDrawStaticSprite(ecs_iter_t *iter)
{
    PCSPRITE sprites = ecs_field(iter, SPRITE, 1);
    PCTRANSFORM transforms = ecs_field(iter, TRANSFORM, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        DrawSprite(&sprites[i], &transforms[i]);
    }
}

static void RenderDrawDynamicSprite(ecs_iter_t *iter)
{
    PCSPRITE sprites = ecs_field(iter, SPRITE, 1);
    PCPHYSICS_BODY bodies = ecs_field(iter, PHYSICS_BODY, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        TRANSFORM transform = bodies[i].transform;
        transform.x *= SPRITE_SIZE;
        transform.y *= SPRITE_SIZE;
        DrawSprite(&sprites[i], &transform);
    }
}

static void RenderDrawCursor(ecs_iter_t *iter)
{
    DrawSprite(&s_cursor,
               &(TRANSFORM){g_input.mouseX - SPRITE_SIZE / 2, g_input.mouseY - SPRITE_SIZE / 2, 0.0f, 1.0f, 1.0f});
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
    ECS_SYSTEM(g_world, RenderDrawCursor, EcsPostUpdate);
    ECS_SYSTEM(g_world, RenderEnd, EcsPostFrame);
}
