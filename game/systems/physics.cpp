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
        bodies[i].xSpeed = body->GetLinearVelocity().x;
        bodies[i].ySpeed = body->GetLinearVelocity().y;
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

    g_physicsWorld = new b2World(b2Vec2(0.0f, GRAVITY));
    if (!g_physicsWorld)
    {
        Error("failed to create physics world");
    }

    ECS_SYSTEM_EX(g_world, PhysicsUpdate, EcsOnUpdate, true, PHYSICS_INTERVAL);
    ECS_SYSTEM(g_world, PhysicsUpdateBodyTransform, EcsOnUpdate, PHYSICS_BODY);

    ecs_atfini(g_world, (ecs_fini_action_t)Shutdown, NULL);
}

extern "C" void CreatePhysicsBody(PPHYSICS_BODY body, f32 x, f32 y, f32 zRotation, f32 width, f32 height,
                                  PHYSICS_BODY_TYPE type, f32 mass, bool fixedRotation)
{
    b2BodyDef def;
    def.position.Set(x, y);
    def.angle = zRotation;
    def.type = (b2BodyType)type;
    def.fixedRotation = fixedRotation;
    
    body->body = WORLD->CreateBody(&def);
    if (!body->body)
    {
        Error("failed to create physics body");
    }

    b2PolygonShape shape;
    shape.SetAsBox(width / 2, height / 2);
    b2MassData massData;
    massData.mass = mass;
    shape.ComputeMass(&massData, mass / width * height);
    ((b2Body *)body->body)->CreateFixture(&shape, 1.0f);
}

extern "C" void ApplyForceToPhysicsBody(PCPHYSICS_BODY body, f32 xSpeed, f32 ySpeed)
{
    ((b2Body *)body->body)->ApplyForceToCenter(b2Vec2(xSpeed, ySpeed), true);
}

extern "C" void GetPhysicsBodyVelocity(PCPHYSICS_BODY body, f32 *x, f32 *y)
{
    *x = ((b2Body *)body->body)->GetLinearVelocity().x;
    *y = ((b2Body *)body->body)->GetLinearVelocity().y;
}

extern "C" void SetPhysicsBodyVelocity(PCPHYSICS_BODY body, f32 x, f32 y)
{
    ((b2Body *)body->body)->SetLinearVelocity(b2Vec2(x, y));
}