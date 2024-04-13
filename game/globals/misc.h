// If this wasn't C you could say something bad about this

#pragma once

#include "game/game.h"

extern SDL_Storage *g_storage;

extern bool g_running;

extern SDL_Window *g_window;
extern struct INPUT_STATE g_input;

// 32 sprites by 18 sprites, also scales good on most screens because 16:9

#define GAME_WIDTH 16 * 16 * 2
#define GAME_HEIGHT 16 * 9 * 2

extern SDL_Renderer *g_renderer;

extern nvSpace *g_space;

extern struct IMAGE g_spriteSheet;

extern ecs_world_t *g_world;

extern ecs_entity_t g_player;
