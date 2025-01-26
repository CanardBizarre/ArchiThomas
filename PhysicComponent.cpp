#include "PhysicComponent.h"
#include "Actor.h"

PhysicComponent::PhysicComponent(Actor* _owner, const float _moveSpeed, const Vector2f _direction, 
								const float _mass) : Component(_owner)
{
	bounceOffset = Vector2f();

	// Movement
	canMove = true;
	moveSpeed = _moveSpeed;

	// Fall
	mass = _mass;
	gravity = 9.81f;
	direction = _direction;
}

PhysicComponent::PhysicComponent(Actor* _owner, const PhysicComponent* _other) : Component(_owner)
{
	bounceOffset = _other->bounceOffset;

	// Movement
	canMove = _other->canMove;
	moveSpeed = _other->moveSpeed;

	// Fall
	mass = _other->mass;
	gravity = _other->gravity;
	direction = _other->direction;
}

Vector2f PhysicComponent::ComputeRebound(const Vector2f& _direction, const Vector2f& _normal, float _restitution)
{
	Vector2f _normalizedNormal = _normal.normalized();
	float _dotProduct = _direction.dot(_normalizedNormal);
	return _direction - _normalizedNormal * ((1 + _restitution) * _dotProduct);
}


void PhysicComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (canMove)
	{

		//// Direction
		//Vector2f _directionOffset = direction * moveSpeed * 100.0f;

		//// Fall
		//const Vector2f& _downVector = Vector2f(0.0f, 1.0f);
		//const Vector2f& _fallOffset = _downVector * gravity * mass;
		//
		//time += _deltaTime;
		////bounceOffset *= EaseOutQuart(0.5f);

		//// Result
		//offset = (_directionOffset + _fallOffset + bounceOffset) * _deltaTime;
		//fallMovement += _fallOffset * _deltaTime;
		//
		//Move(offset);

		Vector2f _directionOffset = direction * moveSpeed * 100.0f;
		const Vector2f& _fallOffset = Vector2f(0.0f, 1.0f) * gravity * mass;
		bounceOffset += (_directionOffset + _fallOffset) * _deltaTime;
		const Vector2f& _offset = bounceOffset * _deltaTime;
		owner->Move(_offset);
	}
}

void PhysicComponent::ApplyBounce()
{
	// Bounce
	const Vector2f _normal = Vector2f(0.0f, -1.0f);
	owner->Move(Vector2f(_normal) * 0.1f);
	bounceOffset = ComputeRebound(bounceOffset, _normal, 0.8f);
}

void PhysicComponent::DEBUG()
{
	//LOG(Warning, direction);
	LOG(Error, bounceOffset);
	//LOG(Display, fallMovement);
	//LOG(Error, offset);
}
