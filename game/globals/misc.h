// If this wasn't C you could say something bad about this

#pragma once

#include "game/game.h"

BEGIN_EXTERN_C

extern SDL_Storage *g_storage;

extern bool g_running;

extern SDL_Window *g_window;
extern u32 g_width; // only needed for mouse position
extern u32 g_height;
extern struct INPUT_STATE g_input;

extern SDL_Renderer *g_renderer;

extern void *g_physicsWorld;

extern struct IMAGE g_spriteSheet;

extern ecs_world_t *g_world;

extern struct CAMERA g_camera;
extern ecs_entity_t g_player;

END_EXTERN_C
