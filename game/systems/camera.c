#include "game/log.h"

#include "game/globals/misc.h"
#include "game/globals/sprites.h"

#include "camera.h"

static void CameraFollowPlayer(ecs_iter_t *iter)
{
    PCPHYSICS_BODY body = ecs_get(g_world, g_player, PHYSICS_BODY);
    g_camera.x = body->transform.x;
    g_camera.y = body->transform.y;
}

void InitializeCameraSystem(void)
{
    LogInfo("Initializing camera system");

    g_camera.x = 0.0f;
    g_camera.y = 0.0f;

    ECS_SYSTEM(g_world, CameraFollowPlayer, EcsOnUpdate);
}

void CameraProject(PCSPRITE sprite, PCTRANSFORM transform, f32 *outX, f32 *outY, f32 *outWidth, f32 *outHeight)
{
    // make relative to camera
    f32 x = (transform->x - g_camera.x) * SPRITE_SIZE;
    f32 y = (transform->y - g_camera.y) * SPRITE_SIZE;

    // transform to top-left https://math.stackexchange.com/questions/1896656/how-do-i-convert-coordinates-from-bottom-left-as-0-0-to-middle-as-0-0
    *outX = x + GAME_WIDTH / 2;
    *outY = -y + GAME_HEIGHT / 2;

    // scale
    *outWidth = sprite->width * transform->xScale;
    *outHeight = sprite->height * transform->yScale;
}

bool CameraVisible(PCSPRITE sprite, PCTRANSFORM transform)
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 width = 0.0f;
    f32 height = 0.0f;
    CameraProject(sprite, transform, &x, &y, &width, &height);

    return (x + width) / 2 > -(GAME_WIDTH / 2) && (x - width) / 2 < (GAME_WIDTH / 2) &&
           (y + height) / 2 > -(GAME_HEIGHT / 2) && (y - height) / 2 < (GAME_HEIGHT / 2);
}
