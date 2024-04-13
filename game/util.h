#pragma once

#include "game.h"

// winnt.h defines this as the same thing but can't leave that up to chance
#undef ARRAYSIZE
#define ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))

extern dstr Format(cstr message, ...);
extern dstr FormatVa(cstr message, va_list args);

extern void Error(cstr message, ...);
