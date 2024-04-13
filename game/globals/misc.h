// If this wasn't C you could say something bad about this

#pragma once

#include "game/game.h"

BEGIN_EXTERN_C

extern SDL_Storage *g_storage;

extern bool g_running;

extern SDL_Window *g_window;
extern struct INPUT_STATE g_input;

#define KEY_LEFT SDL_SCANCODE_A
#define KEY_RIGHT SDL_SCANCODE_D
#define KEY_JUMP SDL_SCANCODE_SPACE
#define KEY_JUMP_ALT SDL_SCANCODE_W
#define KEY_DASH SDL_SCANCODE_LSHIFT
#define KEY_CROUCH SDL_SCANCODE_LCTRL
#define KEY_CROUCH_ALT SDL_SCANCODE_S
#define KEY_MELEE SDL_SCANCODE_V

// 32 sprites by 18 sprites, also scales good on most screens because 16:9

#define SPRITE_SIZE (16)

#define GAME_WIDTH (SPRITE_SIZE * 16 * 2)
#define GAME_HEIGHT (SPRITE_SIZE * 9 * 2)

extern SDL_Renderer *g_renderer;

extern void *g_physicsWorld;

#define GRAVITY 9.81f

extern struct IMAGE g_spriteSheet;

extern ecs_world_t *g_world;

extern ecs_entity_t g_player;

// Average person runs at 8 mph apparently, so 3.576 m/s

#define PLAYER_MASS 80.0f
#define PLAYER_RUN_SPEED 3.576f
#define PLAYER_RUN_ACCELERATION_TIME 3.0f
#define PLAYER_RUN_FORCE PLAYER_MASS * PLAYER_RUN_SPEED / PLAYER_RUN_ACCELERATION_TIME
#define PLAYER_DASH_FACTOR 2.0f
#define PLAYER_JUMP_FORCE PLAYER_MASS * 3.0f

END_EXTERN_C
