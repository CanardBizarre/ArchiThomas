#include "Ball.h"

Ball::Ball(const float _radius) : MeshActor(_radius, 30, "PopCat")
{
	physic = CreateComponent<PhysicComponent>(3.0f, Vector2f(0.0f, 1.0f), 200.0f);
}

Ball::Ball(const Ball& _other) : MeshActor(_other)
{
	physic = CreateComponent<PhysicComponent>(3.0f, Vector2f(0.0f, 1.0f), 200.0f);
}

void Ball::Construct()
{
	Super::Construct();
}
