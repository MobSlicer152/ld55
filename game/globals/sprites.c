#include "sprites.h"
#include "misc.h"

const SPRITE s_player = {&g_spriteSheet, 0, 0, SPRITE_SIZE, SPRITE_SIZE};
const SPRITE s_cursor = {&g_spriteSheet, SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE};
const SPRITE s_ground = {&g_spriteSheet, 0, SPRITE_SIZE * 15, SPRITE_SIZE * 16, SPRITE_SIZE};
