#pragma once

#include "game.h"

// winnt.h defines this as the same thing but can't leave that up to chance
#undef ARRAYSIZE
#define ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))

extern void OpenStorage(void);
extern u8 *Read(cstr path, u64 *size);

extern dstr Format(cstr message, ...);
extern dstr FormatVa(cstr message, va_list args);

extern void Error(cstr message, ...);

extern void EcsLog(s32 Level, cstr File, s32 Line, cstr Message);
extern void *EcsMalloc(ecs_size_t size);
extern void EcsFree(void *block);
extern void *EcsRealloc(void *block, ecs_size_t size);
extern void *EcsCalloc(ecs_size_t size);
