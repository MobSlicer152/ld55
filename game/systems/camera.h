#pragma once

#include "game/game.h"

#include "game/components.h"
#include "game/image.h"

typedef struct CAMERA
{
    f32 x;
    f32 y;
} CAMERA, *PCAMERA;

extern void InitializeCameraSystem(void);
extern void CameraProject(PCSPRITE sprite, PCTRANSFORM transform, f32 *outX, f32 *outY, f32 *outWidth, f32 *outHeight);
extern bool CameraVisible(PCSPRITE sprite, PCTRANSFORM transform);
