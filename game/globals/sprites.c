#include "sprites.h"
#include "misc.h"

static const SPRITE_OFFSET playerFrames[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {2.0f, 0.0f}};
const ANIMATED_SPRITE s_player = {&g_spriteSheet, 0.5f, ARRAYSIZE(playerFrames), playerFrames, 1.0f, 2.0f};
const SPRITE s_cursor = {&g_spriteSheet, {0.0f, 2.0f}, 1.0f, 1.0f};
const SPRITE s_ground = {&g_spriteSheet, {0.0f, 15.0f}, 16.0f, 1.0f};
const SPRITE s_wall = {&g_spriteSheet, {15.0f, 0.0f}, 1.0f, 16.0f};
const SPRITE s_projectiles[ProjectileTypeCount] = {
    {&g_spriteSheet, {1.0f, 2.0f}, 0.5f, 0.5f}, // ProjectileTypeFireball
    {&g_spriteSheet, {1.0f, 2.5f}, 0.5f, 0.5f}, // ProjectileTypeSaw
    {&g_spriteSheet, {1.5f, 2.0f}, 0.5f, 0.5f}  // ProjectileTypeEnergyBolt
};
static const SPRITE_OFFSET explosionFrames[] = {{2.0f, 2.0f}, {2.0f, 4.0f}, {2.0f, 6.0f}};
const ANIMATED_SPRITE s_explosion = {&g_spriteSheet, 0.3f, ARRAYSIZE(explosionFrames), explosionFrames};
