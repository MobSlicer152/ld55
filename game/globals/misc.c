#include "game/image.h"

#include "game/systems/input.h"

#include "misc.h"

SDL_Storage *g_storage;

bool g_running;

SDL_Window *g_window;
INPUT_STATE g_input;

SDL_Renderer *g_renderer;

nvSpace *g_space;

IMAGE g_spriteSheet;

ecs_world_t *g_world;

ecs_entity_t g_player;