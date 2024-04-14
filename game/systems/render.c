#include "game/components.h"
#include "game/image.h"
#include "game/log.h"

#include "game/globals/misc.h"
#include "game/globals/sprites.h"

#include "animation.h"
#include "camera.h"
#include "input.h"
#include "render.h"

static void RenderBegin(ecs_iter_t *iter)
{
    SDL_SetRenderDrawColor(g_renderer, 0, 0xAA, 0xFF, 0);
    SDL_RenderClear(g_renderer);
}

static void DrawSprite(PCSPRITE sprite, PCTRANSFORM transform, bool project, bool flip)
{
    if (!project || CameraVisible(sprite, transform))
    {
        f32 width = project ? 0.0f : sprite->width * SPRITE_SIZE * transform->xScale;
        f32 height = project ? 0.0f : sprite->height * SPRITE_SIZE * transform->yScale;
        f32 x = project ? 0.0f : transform->x - width / 2;
        f32 y = project ? 0.0f : transform->y - height / 2;
        if (project)
        {
            CameraProject(sprite, transform, &x, &y, &width, &height);
        }

        SDL_FRect srcRect = {sprite->offset.x * SPRITE_SIZE, sprite->offset.y * SPRITE_SIZE,
                             sprite->width * SPRITE_SIZE, sprite->height * SPRITE_SIZE};
        SDL_FRect destRect = {x, y, width, height};

        SDL_RenderTextureRotated(g_renderer, sprite->sheet->texture, &srcRect, &destRect, transform->zRotation, NULL,
                                 flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
}

static void RenderDrawStaticSprite(ecs_iter_t *iter)
{
    PCSPRITE sprites = ecs_field(iter, SPRITE, 1);
    PCTRANSFORM transforms = ecs_field(iter, TRANSFORM, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        PCFLIP flip = ecs_get(iter->world, iter->entities[i], FLIP);
        DrawSprite(&sprites[i], &transforms[i], true, flip ? flip->value : false);
    }
}

static void RenderDrawDynamicSprite(ecs_iter_t *iter)
{
    PCSPRITE sprites = ecs_field(iter, SPRITE, 1);
    PCPHYSICS_BODY bodies = ecs_field(iter, PHYSICS_BODY, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        TRANSFORM transform = bodies[i].transform;
        PCFLIP flip = ecs_get(iter->world, iter->entities[i], FLIP);
        DrawSprite(&sprites[i], &transform, true, flip ? flip->value : false);
    }
}

static void RenderDrawAnimatedStaticSprite(ecs_iter_t *iter)
{
    PCANIMATION animations = ecs_field(iter, ANIMATION, 1);
    PCTRANSFORM transforms = ecs_field(iter, TRANSFORM, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        PCFLIP flip = ecs_get(iter->world, iter->entities[i], FLIP);
        SPRITE sprite = {0};
        AnimationGetCurrentFrame(&animations[i], &sprite);
        DrawSprite(&sprite, &transforms[i], true, flip ? flip->value : false);
    }
}

static void RenderDrawAnimatedDynamicSprite(ecs_iter_t *iter)
{
    PCANIMATION animations = ecs_field(iter, ANIMATION, 1);
    PCPHYSICS_BODY bodies = ecs_field(iter, PHYSICS_BODY, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        TRANSFORM transform = bodies[i].transform;
        PCFLIP flip = ecs_get(iter->world, iter->entities[i], FLIP);
        SPRITE sprite = {0};
        AnimationGetCurrentFrame(&animations[i], &sprite);
        DrawSprite(&sprite, &transform, true, flip ? flip->value : false);
    }
}

static void RenderDrawCursor(ecs_iter_t *iter)
{
    DrawSprite(
        &s_cursor,
        &(TRANSFORM){g_input.mouseX - s_cursor.width / 2, g_input.mouseY - s_cursor.height / 2, 0.0f, 1.0f, 1.0f},
        false, false);
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
    ECS_SYSTEM(g_world, RenderDrawAnimatedStaticSprite, EcsPostUpdate, ANIMATION, TRANSFORM);
    ECS_SYSTEM(g_world, RenderDrawAnimatedDynamicSprite, EcsPostUpdate, ANIMATION, PHYSICS_BODY);
    ECS_SYSTEM(g_world, RenderDrawCursor, EcsPostUpdate);
    ECS_SYSTEM(g_world, RenderEnd, EcsPostFrame);
}
