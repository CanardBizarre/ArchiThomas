#include "KinecticComponent.h"
#include "Actor.h"

KinecticComponent::KinecticComponent(Actor* _owner) : MovementComponent(_owner)
{
	angle = 0.0f;
	power = 0.0f;
	initialVelocity = Vector2f();
	initialPosition = Vector2f();
	time = 0.0f;
	isLauched = false;
}

KinecticComponent::KinecticComponent(Actor* _owner, KinecticComponent* _other) : MovementComponent(_owner)
{
	angle = _other->angle;
	power = _other->power;
	initialVelocity = _other->initialVelocity;
	initialPosition = _other->initialPosition;
	time = _other->time;
	isLauched = _other->isLauched;
}

void KinecticComponent::Lauch()
{
	isLauched = true;
	initialVelocity = Vector2f(cos(angle * priv::pi / 180), sin(angle * priv::pi / 180)* power);
	initialPosition = Vector2f(owner->GetPosition().x, owner->GetPosition().y);
}

void KinecticComponent::Move(const float _delta)
{
	if (isLauched)
	{
		time += _delta;

		const float _posX = ComputeKinematicEquation(0, initialVelocity.x, initialPosition.x, time);
		const float _posY = ComputeKinematicEquation(0, initialVelocity.y, initialPosition.y, time);

		owner->SetPosition(Vector2f(_posX, _posY));
	}
}
