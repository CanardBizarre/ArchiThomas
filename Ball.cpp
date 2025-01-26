#include "Ball.h"
#include "TimerManager.h"

Ball::Ball(const float _radius) : MeshActor(_radius)
{
    physic = CreateComponent<PhysicComponent>(40.0f, 0.85f, 0.85f);
    SetOriginAtMiddle();
}

Ball::Ball(const Ball& _other) : MeshActor(_other)
{
    physic = CreateComponent<PhysicComponent>(_other.physic);
    SetOriginAtMiddle();
}
