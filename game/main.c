#include "game.h"

#include "globals.h"
#include "log.h"
#include "window.h"

#include "components/sprite.h"

s32 main(s32 argc, char* argv[])
{
    CreateMainWindow();

    g_world = ecs_init();

    ecs_fini(g_world);
}
