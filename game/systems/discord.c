#include "game/log.h"
#include "game/util.h"

#include "game/globals/misc.h"

#include "discord.h"

static bool connected;
static DiscordUser user;

static void DiscordReady(const DiscordUser *NewUser)
{
    user = *NewUser;
    connected = true;
    LogDebug("Discord connected as %s (%s)", user.username, user.userId);
}

static void DiscordDisconnected(s32 error, cstr message)
{
    connected = false;
    memset(&user, 0, sizeof(DiscordUser));

    if (message && error != 0)
    {
        LogError("Discord disconnected: %s (%d)", message, error);
    }
    else
    {
        LogDebug("Discord disconnected%s%s", message ? ": " : "", message ? message : "");
    }
}

static const u64 friendIds[] = {570760243341033472, 802941540120789014, 691017722934329394, 436582998171844608,
                                744607381991718913, 526963318867492865, 878017826558996570, 898953887988482068,
                                751186390598811739, 700010638730330122, 887865846414868521, 551486661079334912,
                                344253142952574989, 343862296751112192, 515919551444025407, 725427722293215332,
                                464268944459563018, 405454975750373376};

static bool IsFriend(u64 Id)
{
    for (usize i = 0; i < ARRAYSIZE(friendIds); i++)
    {
        if (friendIds[i] == Id)
        {
            return true;
        }
    }

    return false;
}

static cstr DiscordGetGameString()
{
    u64 userId = strtoll(user.userId ? user.userId : "", NULL, 10);
    switch (userId)
    {
    case 532320702611587112:
        return "my game ";
    case 1078816552629051423:
        return "my brother's game ";
    default:
        if (IsFriend(userId))
        {
            return "my friend's game ";
        }
        else
        {
            return "";
        }
    }
}

static void DiscordUpdate(_In_ ecs_iter_t *iter)
{
    SDL_RendererInfo rendererInfo = {0};
    SDL_GetRendererInfo(g_renderer, &rendererInfo);

    char state[128] = {0};
    char details[128] = {0};

    DiscordRichPresence presence = {0};
    presence.state = state;
#ifdef GAME_DEBUG
    snprintf(state, ARRAYSIZE(state), "Testing %s on %s", DiscordGetGameString(), SDL_GetPlatform());
#else
    snprintf(state, ARRAYSIZE(state), "Playing %son %s", DiscordGetGameString(), SDL_GetPlatform());
#endif
    presence.details = details;
    snprintf(details, ARRAYSIZE(details),
             "v" GAME_VERSION_STRING " commit " GAME_COMMIT "-" GAME_BRANCH ", " GAME_BUILD_TYPE " build, %s renderer",
             rendererInfo.name);

    Discord_UpdatePresence(&presence);

    Discord_RunCallbacks();
}

static void DiscordShutdown(void)
{
    LogInfo("Shutting down Discord");
    Discord_ClearPresence();
    Discord_Shutdown();
    DiscordDisconnected(0, NULL);
}

void InitializeDiscordSystem(void)
{
    LogInfo("Attempting to initialize Discord");

    DiscordEventHandlers eventHandlers = {0};
    eventHandlers.ready = DiscordReady;
    eventHandlers.disconnected = DiscordDisconnected;
    eventHandlers.errored = DiscordDisconnected;
    Discord_Initialize(GAME_DISCORD_APP_ID, &eventHandlers, true, NULL);

    ECS_SYSTEM_EX(g_world, DiscordUpdate, EcsOnUpdate, false, DISCORD_INTERVAL);

    ecs_atfini(g_world, (ecs_fini_action_t)DiscordShutdown, NULL);
}
