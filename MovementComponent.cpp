#include "MovementComponent.h"
#include "Actor.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	speed = 100.0f;
	direction = Vector2f(1.0f, 0.0f);
	rotateSpeed = 10.0f;
	target = nullptr;
}

MovementComponent::MovementComponent(Actor* _owner, const MovementComponent* _other) : Component(_owner)
{
	speed = _other->speed;
	direction = _other->direction;
	rotateSpeed = _other->rotateSpeed;
	target = _other->target;
}


void MovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	//Move(_deltaTime);
	RotateAround(_deltaTime);
}


void MovementComponent::Move(const float _deltaTime)
{
	const Vector2f& _offset = direction * speed * _deltaTime;
	owner->Move(_offset);
}

void MovementComponent::RotateAround(const float _deltaTime)
{
	if (!target) return; 
	const Vector2f& _center = target->GetPosition();
	const Vector2f& _relativePos = owner->GetPosition() - _center;
	const float _radAngle = DegToRad(rotateSpeed * _deltaTime);
	const float _newPosX = _relativePos.x * cos(rotateSpeed) - _relativePos.y * sin(rotateSpeed);
	const float _newPosY = _relativePos.x * sin(rotateSpeed) + _relativePos.y * cos(rotateSpeed);
	const Vector2f& _newPosition = _center + Vector2f(_newPosX, _newPosY);
	owner->SetPosition(_newPosition);
}
