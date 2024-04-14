#include "game/log.h"

#include "game/globals/misc.h"

#include "animation.h"

static void AnimationTick(ecs_iter_t* iter)
{
    PANIMATION animations = ecs_field(iter, ANIMATION, 1);

    for (s32 i = 0; i < iter->count; i++)
    {
        PANIMATION animation = &animations[i];
        if (!animation->paused)
        {
            animation->timeSinceLastFrame += iter->delta_system_time;
            if (animation->timeSinceLastFrame > animation->frames->frameTime)
            {
                WRAPPED_INCREMENT(animation->currentFrame, animation->minFrame, MIN(animation->maxFrame + 1, animation->frames->frameCount));
                animation->timeSinceLastFrame = 0.0f;
            }
        }
    }
}

void InitializeAnimationSystem(void)
{
    LogInfo("Initializing animation system");

    ECS_SYSTEM(g_world, AnimationTick, EcsOnUpdate, ANIMATION);
}

void AnimationGetCurrentFrame(PCANIMATION animation, PSPRITE sprite)
{
    sprite->sheet = animation->frames->sheet;
    sprite->width = animation->frames->width;
    sprite->height = animation->frames->height;
    sprite->offset.x = animation->frames->frames[animation->currentFrame].x;
    sprite->offset.y = animation->frames->frames[animation->currentFrame].y;
}
