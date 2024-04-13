#include "box2d/box2d.h"

#include "game/log.h"
#include "game/util.h"

#include "game/globals/misc.h"

#include "physics.h"

#define WORLD ((b2World *)g_physicsWorld)

static void PhysicsUpdate(ecs_iter_t *iter)
{
    WORLD->Step(iter->delta_system_time, 6, 2);
}

static void PhysicsUpdateBodyTransform(ecs_iter_t *iter)
{
    PPHYSICS_BODY bodies = ecs_field(iter, PHYSICS_BODY, 1);

    for (s32 i = 0; i < iter->count; i++)
    {
        b2Body *body = (b2Body *)bodies[i].body;
        bodies[i].transform.x = body->GetPosition().x;
        bodies[i].transform.y = body->GetPosition().y;
        bodies[i].transform.zRotation = body->GetAngle();
        bodies[i].transform.xScale = 1.0f;
        bodies[i].transform.yScale = 1.0f;
    }
}

static void Shutdown(void)
{
    LogInfo("Shutting down physics system");
    delete g_physicsWorld;
}

extern "C" void InitializePhysicsSystem(void)
{
    LogInfo("Initializing physics system");

    g_physicsWorld = new b2World(b2Vec2(0.0f, 9.81f));
    if (!g_physicsWorld)
    {
        Error("failed to create physics world");
    }

    ECS_SYSTEM_EX(g_world, PhysicsUpdate, EcsOnUpdate, true, PHYSICS_INTERVAL);
    ECS_SYSTEM(g_world, PhysicsUpdateBodyTransform, EcsOnUpdate, PHYSICS_BODY);

    ecs_atfini(g_world, (ecs_fini_action_t)Shutdown, NULL);
}

extern "C" void CreatePhysicsBody(PPHYSICS_BODY body, f32 x, f32 y, f32 zRotation, f32 width, f32 height,
                                  PHYSICS_BODY_TYPE type)
{
    b2BodyDef def;
    def.position = b2Vec2(x, y);
    def.angle = zRotation;
    def.type = (b2BodyType)type;
    def.gravityScale = 1.0f;
    body->body = WORLD->CreateBody(&def);
    b2PolygonShape shape;
    shape.SetAsBox(width / 2, height / 2);
    ((b2Body *)body->body)->CreateFixture(&shape, type == PhysicsBodyTypeStatic ? 0.0f : 1.0f);
}

extern "C" void ApplyForceToPhysicsBody(PPHYSICS_BODY body, f32 xForce, f32 yForce, f32 pointX, f32 pointY)
{
    ((b2Body *)body->body)->ApplyForce(b2Vec2(xForce, yForce), b2Vec2(pointX, pointY), true);
}