#pragma once

#include "config.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flecs.h"

#if USE_MIMALLOC
#include "mimalloc.h"
#endif

#include "novaphysics/novaphysics.h"

#define QOI_MALLOC mi_malloc
#define QOI_FREE mi_free
#define QOI_NO_STDIO
#include "qoi.h"

#include "SDL3/SDL.h"

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
