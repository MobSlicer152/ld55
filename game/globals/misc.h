// If this wasn't C you could say something bad about this

#pragma once

#include "game/game.h"

BEGIN_EXTERN_C

#define PI (3.14159265359)
#define DEG2RAD (PI / 180)
#define RAD2DEG (180 / PI)

extern SDL_Storage *g_storage;

extern bool g_running;

extern SDL_Window *g_window;
extern u32 g_width; // only needed for mouse position
extern u32 g_height;
extern struct INPUT_STATE g_input;

// 32 sprites by 18 sprites, also scales good on most screens because 16:9

#define SPRITE_SIZE (16)

#define GAME_WIDTH (SPRITE_SIZE * 16 * 2)
#define GAME_HEIGHT (SPRITE_SIZE * 9 * 2)

extern SDL_Renderer *g_renderer;

extern void *g_physicsWorld;

#define GRAVITY (-9.81f)

extern struct IMAGE g_spriteSheet;

extern ecs_world_t *g_world;

extern struct CAMERA g_camera;
extern ecs_entity_t g_player;

END_EXTERN_C
