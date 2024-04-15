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

static void DrawSprite(PCSPRITE sprite, PCPOSITION position, PCROTATION rotation, bool project, bool flip)
{
    if (!project || CameraVisible(sprite, position))
    {
        f32 x = 0.0f;
        f32 y = 0.0f;
        f32 width = 0.0f;
        f32 height = 0.0f;
        if (project)
        {
            CameraProject(sprite, position, &x, &y, &width, &height);
        }
        else
        {
            width = sprite->width * SPRITE_SIZE;
            height = sprite->height * SPRITE_SIZE;
            x = position->x - width / 2;
            y = position->y - height / 2;
        }

        SDL_FRect srcRect = {sprite->offset.x * SPRITE_SIZE, sprite->offset.y * SPRITE_SIZE,
                             sprite->width * SPRITE_SIZE, sprite->height * SPRITE_SIZE};
        SDL_FRect destRect = {x, y, width, height};

        SDL_RenderTextureRotated(g_renderer, sprite->sheet->texture, &srcRect, &destRect,
                                 rotation ? rotation->value : 0.0f, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
}

static void RenderDrawSprite(ecs_iter_t *iter)
{
    PCSPRITE sprites = ecs_field(iter, SPRITE, 1);
    PCPOSITION positions = ecs_field(iter, POSITION, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        PCROTATION rotation = ecs_get(iter->world, iter->entities[i], ROTATION);
        PCFLIP flip = ecs_get(iter->world, iter->entities[i], FLIP);
        DrawSprite(&sprites[i], &positions[i], rotation, true, flip ? flip->value : false);
    }
}

static void RenderDrawAnimatedSprite(ecs_iter_t *iter)
{
    PCANIMATION animations = ecs_field(iter, ANIMATION, 1);
    PCPOSITION positions = ecs_field(iter, POSITION, 2);

    for (s32 i = 0; i < iter->count; i++)
    {
        PCROTATION rotation = ecs_get(iter->world, iter->entities[i], ROTATION);
        PCFLIP flip = ecs_get(iter->world, iter->entities[i], FLIP);
        SPRITE sprite = {0};
        AnimationGetCurrentFrame(&animations[i], &sprite);
        DrawSprite(&sprite, &positions[i], rotation, true, flip ? flip->value : false);
    }
}

static void RenderDrawCursor(ecs_iter_t *iter)
{
    DrawSprite(&s_cursor, &(POSITION){g_input.mouseX - s_cursor.width / 2, g_input.mouseY - s_cursor.height / 2}, NULL,
               false, false);
}

static void RenderDrawInfo(ecs_iter_t *iter)
{
    DrawSprite(&s_info,
               &(POSITION){GAME_WIDTH / 2 - s_info.width / 2, GAME_HEIGHT / 2 - s_info.height / 2 - SPRITE_SIZE * 3},
               NULL, false, false);
}

static void RenderEnd(ecs_iter_t *iter)
{
    SDL_RenderPresent(g_renderer);
}

void InitializeRenderSystem(void)
{
    LogInfo("Initializing render system");

    ECS_SYSTEM(g_world, RenderBegin, EcsPreFrame);
    ECS_SYSTEM(g_world, RenderDrawSprite, EcsPostUpdate, SPRITE, POSITION);
    ECS_SYSTEM(g_world, RenderDrawAnimatedSprite, EcsPostUpdate, ANIMATION, POSITION);
    ECS_SYSTEM(g_world, RenderDrawCursor, EcsPostUpdate);
    ECS_SYSTEM(g_world, RenderDrawInfo, EcsPostUpdate);
    ECS_SYSTEM(g_world, RenderEnd, EcsPostFrame);
}
