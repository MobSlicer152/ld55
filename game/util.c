#include "globals.h"
#include "log.h"
#include "util.h"

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
    s32 size = vsnprintf(NULL, 0, message, copiedArgs);
    if (!size)
    {
        return 0;
    }

    dstr buffer = mi_calloc(size, sizeof(char));
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
