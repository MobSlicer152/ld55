#include "game/log.h"

#include "game/globals/misc.h"
#include "game/globals/sprites.h"

#include "camera.h"

static void CameraFollowPlayer(ecs_iter_t *iter)
{
    PCPOSITION position = ecs_get(g_world, g_player, POSITION);
    g_camera.x = position->x;
    g_camera.y = position->y;
}

void InitializeCameraSystem(void)
{
    LogInfo("Initializing camera system");

    g_camera.x = 0.0f;
    g_camera.y = 0.0f;

    ECS_SYSTEM(g_world, CameraFollowPlayer, EcsOnUpdate);
}

void CameraProject(PCSPRITE sprite, PCPOSITION position, f32 *outX, f32 *outY, f32 *outWidth, f32 *outHeight)
{
    f32 centerX = 0.0f;
    f32 centerY = 0.0f;

    if (sprite)
    {
        // scale
        *outWidth = sprite->width * SPRITE_SIZE;
        *outHeight = sprite->height * SPRITE_SIZE;
        centerX = *outWidth / 2;
        centerY = *outHeight / 2;
    }

    // make relative to camera
    f32 cameraX = (position->x - g_camera.x) * SPRITE_SIZE - centerX;
    f32 cameraY = (position->y - g_camera.y) * SPRITE_SIZE + centerY;

    // get top-left relative for screen
    // https://math.stackexchange.com/questions/1896656/how-do-i-convert-coordinates-from-bottom-left-as-0-0-to-middle-as-0-0
    *outX = cameraX + GAME_WIDTH / 2;
    *outY = -cameraY + GAME_HEIGHT / 2;
}

bool CameraVisible(PCSPRITE sprite, PCPOSITION position)
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 width = 0.0f;
    f32 height = 0.0f;
    CameraProject(sprite, position, &x, &y, &width, &height);

    return (x + width) / 2 > -(GAME_WIDTH / 2) && (x - width) / 2 < (GAME_WIDTH / 2) &&
           (y + height) / 2 > -(GAME_HEIGHT / 2) && (y - height) / 2 < (GAME_HEIGHT / 2);
}
