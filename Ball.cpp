#include "Ball.h"


Ball::Ball(const float _radius) : MeshActor(_radius, 30, "PopCat")
{
	movement = CreateComponent<KinecticComponent>();
}

Ball::Ball(const Ball& _other) : MeshActor(_other)
{
	movement = CreateComponent<KinecticComponent>(_other.movement);
}


void Ball::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}


