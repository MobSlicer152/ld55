#include "globals.h"
#include "spritesheet.h"

SDL_Storage *g_storage;

ecs_world_t *g_world;

bool g_running;

SDL_Window *g_window;

SDL_Renderer *g_renderer;

SPRITE_SHEET g_spriteSheet;

ecs_entity_t g_player;