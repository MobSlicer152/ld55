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
