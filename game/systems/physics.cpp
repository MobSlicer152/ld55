#include "box2d/box2d.h"

#include "game/log.h"
#include "game/util.h"

#include "game/globals/misc.h"

#include "camera.h"
#include "physics.h"

#define WORLD ((b2World *)g_physicsWorld)

static void PhysicsUpdate(ecs_iter_t *iter)
{
    WORLD->Step(iter->delta_system_time, 6, 2);
}

static void PhysicsDebugDraw(ecs_iter_t *iter)
{
    WORLD->DebugDraw();
}

static void PhysicsUpdateBody(ecs_iter_t *iter)
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

#ifdef GAME_DEBUG
// TODO: make this work, and less janky
class CPhysicsDebugDraw : public b2Draw
{
    static void ConvertAndProjectVertices(const b2Vec2 *inputVertices, s32 count, SDL_FPoint *vertices, s32 outCount,
                                          const b2Color &color)
    {
        for (s32 i = 0; i < count && i < outCount; i++)
        {
            vertices[i].x = inputVertices[i].x;
            vertices[i].y = inputVertices[i].y;
            TRANSFORM transform = {vertices[i].x, vertices[i].y};
            CameraProject(nullptr, &transform, &vertices[i].x, &vertices[i].y, nullptr, nullptr);

            // vertices[i].color.r = color.r;
            // vertices[i].color.g = color.g;
            // vertices[i].color.b = color.b;
            // vertices[i].color.a = color.a;
        }
    }

    void DrawPolygon(const b2Vec2 *vertices, s32 vertexCount, const b2Color &color) override
    {
        SDL_FPoint convertedVertices[6];
        ConvertAndProjectVertices(vertices, vertexCount, convertedVertices, ARRAYSIZE(convertedVertices), color);
        SDL_SetRenderDrawColorFloat(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderLines(g_renderer, (SDL_FPoint *)convertedVertices, vertexCount);
    }

    void DrawSolidPolygon(const b2Vec2 *vertices, s32 vertexCount, const b2Color &color) override
    {
        DrawPolygon(vertices, vertexCount, color);
    }

    void DrawCircle(const b2Vec2 &center, f32 radius, const b2Color &color) override
    {
        SDL_SetRenderDrawColorFloat(g_renderer, color.r, color.g, color.b, color.a);
    }

    void DrawSolidCircle(const b2Vec2 &center, f32 radius, const b2Vec2 &axis, const b2Color &color) override
    {
        SDL_SetRenderDrawColorFloat(g_renderer, color.r, color.g, color.b, color.a);
        // SDL_Render
    }

    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override
    {
        SDL_SetRenderDrawColorFloat(g_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderLine(g_renderer, p1.x, p1.y, p2.x, p2.y);
    }

    void DrawTransform(const b2Transform &xf) override
    {
    }

    void DrawPoint(const b2Vec2 &p, f32 size, const b2Color &color) override
    {
    }
};

static CPhysicsDebugDraw debugDraw;
#endif

extern "C" void InitializePhysicsSystem(void)
{
    LogInfo("Initializing physics system");

    g_physicsWorld = new b2World(b2Vec2(0.0f, GRAVITY));
    if (!g_physicsWorld)
    {
        Error("failed to create physics world");
    }

    ECS_SYSTEM_EX(g_world, PhysicsUpdate, EcsOnUpdate, true, PHYSICS_INTERVAL);
    ECS_SYSTEM(g_world, PhysicsUpdateBody, EcsOnUpdate, PHYSICS_BODY);

#ifdef GAME_DEBUG
    debugDraw.SetFlags(CPhysicsDebugDraw::e_shapeBit);
    WORLD->SetDebugDraw((b2Draw *)&debugDraw);

    ECS_SYSTEM(g_world, PhysicsDebugDraw, EcsPostUpdate);
#endif

    ecs_atfini(g_world, (ecs_fini_action_t)Shutdown, nullptr);
}

static void AddCollider(b2Body *body, PCPHYSICS_COLLIDER_DESC collider)
{
    b2MassData massData;
    massData.mass = collider->mass;

    switch (collider->shape)
    {
    case PhysicsColliderShapeRect: {
        b2PolygonShape rectShape;
        rectShape.SetAsBox(collider->width / 2, collider->height / 2, b2Vec2(collider->x, collider->y),
                           collider->zRotation * DEG2RAD);
        // rectShape.ComputeMass(&massData, );
        body->CreateFixture(&rectShape, collider->mass / collider->width * collider->height);
        break;
    }
    case PhysicsColliderShapeCircle: {
        b2CircleShape circleShape;
        circleShape.m_radius = (collider->width + collider->height) / 4;
        circleShape.m_p = b2Vec2(collider->x, collider->y);
        // circleShape.ComputeMass(&massData, );
        body->CreateFixture(&circleShape, collider->mass / PI * circleShape.m_radius * circleShape.m_radius);
        break;
    }
    }
}

extern "C" void CreatePhysicsBody(PPHYSICS_BODY body, f32 x, f32 y, PHYSICS_BODY_TYPE type, bool allowRotation,
                                  PCPHYSICS_COLLIDER_DESC colliders, u32 colliderCount)
{
    b2BodyDef def;
    def.position.Set(x, y);
    def.type = (b2BodyType)type;
    def.fixedRotation = !allowRotation;

    b2Body *bodyReal = WORLD->CreateBody(&def);
    if (!bodyReal)
    {
        Error("failed to create physics body");
    }

    for (u32 i = 0; i < colliderCount; i++)
    {
        AddCollider(bodyReal, &colliders[i]);
    }

    body->body = bodyReal;
}

extern "C" void ApplyForceToPhysicsBody(PCPHYSICS_BODY body, f32 xSpeed, f32 ySpeed)
{
    ((b2Body *)body->body)->ApplyLinearImpulseToCenter(b2Vec2(xSpeed, ySpeed), true);
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