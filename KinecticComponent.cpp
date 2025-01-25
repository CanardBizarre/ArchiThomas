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
	if (!isLauched)
	{
		isLauched = true;
		initialVelocity = Vector2f(cos(angle * priv::pi / 180), sin(angle * priv::pi / 180)) * power;
		initialPosition = Vector2f(owner->GetPosition().x, owner->GetPosition().y);
	}

}

void KinecticComponent::Move(const float _delta)
{
	if (isLauched)
	{
		time += _delta * 10.0f;
		LOG(Display, "time is : " +to_string(time));
		const float _posX = ComputeKinematicEquation(0, initialVelocity.x, initialPosition.x, time);
		const float _posY = ComputeKinematicEquation(9.81f, initialVelocity.y, initialPosition.y, time);
		LOG(Display, "pos X is : " +to_string(_posX) + "pos Y is : " + to_string(_posY));

		owner->SetPosition(Vector2f(_posX, _posY));
	}
}
