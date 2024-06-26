#include "util.h"
#include "globals/misc.h"
#include "log.h"

void OpenStorage(void)
{
    cstr path = "assets";

    LogInfo("Opening storage in %s", path);
    g_storage = SDL_OpenFileStorage(path);
    if (!g_storage)
    {
        Error("Failed to open storage %s: %s", path, SDL_GetError());
    }

    while (!SDL_StorageReady(g_storage))
    {
        LogInfo("Waiting 1 second for storage");
        SDL_Delay(1000);
    }
}

u8 *Read(cstr path, u64 *size)
{
    if (SDL_GetStorageFileSize(g_storage, path, size) < 0 || *size < 1)
    {
        Error("failed to read file %s or it was empty: %s", path, SDL_GetError());
    }

    u8 *data = CALLOC(1, *size);
    if (!data)
    {
        Error("failed to allocate memory for file %s", path);
    }

    if (SDL_ReadStorageFile(g_storage, path, data, *size) < 0)
    {
        Error("failed to read file %s: %s", path, SDL_GetError());
    }

    return data;
}

dstr Format(cstr message, ...)
{
    va_list args;

    va_start(args, message);
    dstr buffer = FormatVa(message, args);
    va_end(args);

    return buffer;
}

dstr FormatVa(cstr message, va_list args)
{
    va_list copiedArgs;
    va_copy(copiedArgs, args);

    // why snprintf gotta return int but take size_t like what the fuck
    s32 size = vsnprintf(NULL, 0, message, copiedArgs) + 1;
    if (!size)
    {
        return 0;
    }

    dstr buffer = CALLOC(size, sizeof(char));
    if (!buffer)
    {
        Error("failed to allocate memory in FormatVa");
    }

    vsnprintf(buffer, size, message, copiedArgs);
    va_end(copiedArgs);

    return buffer;
}

void Error(cstr message, ...)
{
    va_list args;
    va_start(args, message);
    // so FormatVa can report OOM
    char buffer[1024];
    vsnprintf(buffer, ARRAYSIZE(buffer), message, args);
    va_end(args);

    LogFatal("Fatal error: %s", buffer);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", buffer, g_window);
    abort();
}

f32 Magnitude(f32 x, f32 y)
{
    return sqrt(x * x + y * y);
}

void Normalize(f32 *x, f32 *y)
{
    f32 magnitude = Magnitude(*x, *y);
    *x /= magnitude;
    *y /= magnitude;
}

f32 Lerp(f32 current, f32 target, f32 deltaTime)
{
    return current * (1.0f - deltaTime) + (target * deltaTime);
}

void EcsLog(s32 Level, cstr File, s32 Line, cstr Message)
{
    LOG_LEVEL RealLevel;

    switch (Level)
    {
    case 0:
        RealLevel = LogLevelTrace;
        break;
    case -2:
        RealLevel = LogLevelWarning;
        break;
    case -3:
        RealLevel = LogLevelError;
        break;
    case -4:
        RealLevel = LogLevelFatal;
        break;
    default:
        RealLevel = LogLevelDebug;
        break;
    }

    RealLevel = LogLevelTrace;

    if (RealLevel == LogLevelFatal)
    {
        Error("ECS error at %s:%d: %s", File, Line, Message);
    }
    else
    {
        LogMessage(RealLevel, File, Line, false, "%s", Message);
    }
}

void *EcsMalloc(ecs_size_t size)
{
    return MALLOC(size);
}

void EcsFree(void *block)
{
    FREE(block);
}

void *EcsRealloc(void *block, ecs_size_t size)
{
    return REALLOC(block, size);
}

void *EcsCalloc(ecs_size_t size)
{
    return CALLOC(1, size);
}
