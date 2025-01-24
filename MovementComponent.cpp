#include "MovementComponent.h"
#include "Actor.h"


MovementComponent::MovementComponent(Actor* _owner, vector<MovementType> _movementsAction) : Component(_owner)
{
	speed = 1.0f;
	direction = Vector2f(1.0f, 0.0f);
	rotateSpeed = 30.0f;
	target = nullptr;
	movementsAction = _movementsAction;
}

MovementComponent::MovementComponent(Actor* _owner, const MovementComponent* _other) : Component(_owner)
{
	speed = _other->speed;
	direction = _other->direction;
	rotateSpeed = _other->rotateSpeed;
	target = _other->target;
	movementsAction = _other->movementsAction;
}


void MovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	vector<function<void()>> _callBacks
	{
		[&]() {Move(_deltaTime); },
		[&]() {RotateAround(_deltaTime); },
		[&]() {RotateToTarget(_deltaTime); },
	};
	for (MovementType _action : movementsAction)
	{
		_callBacks[_action]();
	}
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
	const float _newPosX = _relativePos.x * cos(_radAngle) - _relativePos.y * sin(_radAngle);
	const float _newPosY = _relativePos.x * sin(_radAngle) + _relativePos.y * cos(_radAngle);
	const Vector2f& _newPosition = _center + Vector2f(_newPosX, _newPosY);
	owner->SetPosition(_newPosition);
	owner->Rotate(radians(_radAngle));
}

void MovementComponent::RotateToTarget(const float _deltaTime)
{
	const Vector2f& _center = target->GetPosition();
	const Vector2f& _relativePos = owner->GetPosition() - _center;
	const float _radAngle = DegToRad(rotateSpeed * _deltaTime);
	owner->Rotate(radians(_radAngle));
}
