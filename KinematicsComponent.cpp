#include "KinematicsComponent.h"
#include "Actor.h"

KinematicsComponent::KinematicsComponent(Actor* _owner, const float _power, const float _angle)
	: MovementComponent(_owner)
{
	angle = _angle;
	power = _power;
	initialVelocity = Vector2f();
	initialPosition = Vector2f();
	time = 0.0f;
	isLauched = false;
}

KinematicsComponent::KinematicsComponent(Actor* _owner, KinematicsComponent* _other) : MovementComponent(_owner)
{
	angle = _other->angle;
	power = _other->power;
	initialVelocity = _other->initialVelocity;
	initialPosition = _other->initialPosition;
	time = _other->time;
	isLauched = _other->isLauched;
}

void KinematicsComponent::Lauch()
{
	if (!isLauched)
	{
		isLauched = true;
		initialVelocity = Vector2f(cos(angle * priv::pi / 180), sin(angle * priv::pi / 180)) * power;
		initialPosition = Vector2f(owner->GetPosition().x, owner->GetPosition().y);
	}

}

void KinematicsComponent::Move(const float _delta)
{
	if (isLauched)
	{
		Vector2f newCoordinate = ComputeNewCoordinate(_delta);
		owner->SetPosition(newCoordinate);
	}
}

Vector2f KinematicsComponent::ComputeNewCoordinate(const float _delta)
{
	time += _delta * 10.0f;
	const float _posX = ComputeKinematicEquation(0, initialVelocity.x, initialPosition.x, time);
	const float _posY = ComputeKinematicEquation(9.81f, initialVelocity.y, initialPosition.y, time);
	return Vector2f(_posX, _posY);
}
