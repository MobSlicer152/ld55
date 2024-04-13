// If this wasn't C you could say something bad about this

#pragma once

#include "game.h"

extern SDL_Storage *g_storage;

extern ecs_world_t *g_world;

extern bool g_running;

extern SDL_Window *g_window;

// 32 sprites by 18 sprites, also scales good on most screens

#define GAME_WIDTH 16 * 16 * 2
#define GAME_HEIGHT 16 * 9 * 2

extern SDL_Renderer *g_renderer;

extern struct SPRITE_SHEET g_spriteSheet;

extern ecs_entity_t g_player;
