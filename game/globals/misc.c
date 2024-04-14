#include "game/image.h"

#include "game/systems/camera.h"
#include "game/systems/input.h"

#include "misc.h"

SDL_Storage *g_storage;

bool g_running;

SDL_Window *g_window;
u32 g_width;
u32 g_height;
INPUT_STATE g_input;

SDL_Renderer *g_renderer;

void *g_physicsWorld;

IMAGE g_spriteSheet;

ecs_world_t *g_world;

CAMERA g_camera;
ecs_entity_t g_player;
