#pragma once

#include "game.h"

BEGIN_EXTERN_C

#define MAKETAG(type, name, ...) typedef type name __VA_ARGS__ name, *P##name; typedef type name const *PC##name;
#define MAKECOMPONENT(type, name, ...) MAKETAG(type, name, __VA_ARGS__) extern ECS_COMPONENT_DECLARE(name);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, min, max) ((value) > (max) ? (max) : (value) < (min) ? (min) : (value))

#define WRAPPED_ADD(value, add, min, max) ((value) = CLAMP(((value) + 1) % (max), (min), (max)))
#define WRAPPED_INCREMENT(value, min, max) WRAPPED_ADD((value), 1, (min), (max))

// winnt.h defines this as the same thing but can't leave that up to chance
#undef ARRAYSIZE
#define ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))

extern void OpenStorage(void);
extern u8 *Read(cstr path, u64 *size);

extern dstr Format(cstr message, ...);
extern dstr FormatVa(cstr message, va_list args);

extern void Error(cstr message, ...);

extern f32 Magnitude(f32 x, f32 y);
extern void Normalize(f32 *x, f32 *y);
extern f32 Lerp(f32 current, f32 target, f32 deltaTime);

#define ECS_SYSTEM_DEFINE_EX(world, id_, phase, multi_threaded_, interval_, ...)                                       \
    {                                                                                                                  \
        ecs_system_desc_t desc = {0};                                                                                  \
        ecs_entity_desc_t edesc = {0};                                                                                 \
        edesc.id = ecs_id(id_);                                                                                        \
        edesc.name = #id_;                                                                                             \
        edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);                                                \
        edesc.add[1] = (phase);                                                                                        \
        desc.entity = ecs_entity_init(world, &edesc);                                                                  \
        desc.query.filter.expr = #__VA_ARGS__;                                                                         \
        desc.callback = id_;                                                                                           \
        desc.multi_threaded = (multi_threaded_);                                                                       \
        desc.interval = (interval_);                                                                                   \
        ecs_id(id_) = ecs_system_init(world, &desc);                                                                   \
    }                                                                                                                  \
    ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL)

#define ECS_SYSTEM_EX(world, id, phase, multi_threaded, interval, ...)                                                 \
    ecs_entity_t ecs_id(id) = 0;                                                                                       \
    ECS_SYSTEM_DEFINE_EX(world, id, phase, multi_threaded, interval, __VA_ARGS__);                                     \
    ecs_entity_t id = ecs_id(id);                                                                                      \
    (void)ecs_id(id);                                                                                                  \
    (void)id

extern void EcsLog(s32 Level, cstr File, s32 Line, cstr Message);
extern void *EcsMalloc(ecs_size_t size);
extern void EcsFree(void *block);
extern void *EcsRealloc(void *block, ecs_size_t size);
extern void *EcsCalloc(ecs_size_t size);

END_EXTERN_C
