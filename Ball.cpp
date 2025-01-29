#include "Ball.h"


Ball::Ball(const float _radius) : MeshActor(_radius, 30, "PopCat")
{
	movement = CreateComponent<KinematicsComponent>();
}

Ball::Ball(const Ball& _other) : MeshActor(_other)
{
	movement = CreateComponent<KinematicsComponent>(_other.movement);
}


void Ball::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}


