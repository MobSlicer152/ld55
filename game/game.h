#pragma once

#include "config.h"

#include "float.h"
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord_rpc.h"

#include "flecs.h"

#include "SDL3/SDL.h"

#if USE_MIMALLOC
#include "mimalloc.h"

#define MALLOC mi_malloc
#define CALLOC mi_calloc
#define REALLOC mi_realloc
#define FREE mi_free
#else
#define MALLOC SDL_malloc
#define CALLOC SDL_calloc
#define REALLOC SDL_realloc
#define FREE SDL_free
#endif

#define QOI_MALLOC MALLOC
#define QOI_FREE FREE
#define QOI_ZEROARR(a) SDL_memset((a), 0, sizeof(a))
#define QOI_NO_STDIO
#include "qoi.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintptr_t uptr;
typedef uptr usize;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef intptr_t sptr;
typedef sptr ssize;
typedef float f32;
typedef double f64;
typedef char *dstr;
typedef const char *cstr;

#ifdef __cplusplus
#define BEGIN_EXTERN_C extern "C" {
#define END_EXTERN_C }
#else
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif
