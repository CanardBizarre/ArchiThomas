#include "Ball.h"

Ball::Ball(const float _radius) : MeshActor(_radius, 30, "PopCat")
{
	// Movement
	canMove = true;
	moveSpeed = 1.0f;

	// Fall
	time = 0;
	mass = 200.0f;
	gravity = 9.81f;
	direction = Vector2f(1.0f,1.0f);
	fallMovement = Vector2f();
}


void Ball::Tick(const float _deltaTime)
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
		Move(_offset);
	}
}

void Ball::DEBUG()
{
	//LOG(Warning, direction);
	LOG(Error, bounceOffset);
	//LOG(Display, fallMovement);
	//LOG(Error, offset);
}

Vector2f Ball::ComputeRebound(const Vector2f& _direction, const Vector2f& _normal, float _restitution)
{
	Vector2f _normalizedNormal = _normal.normalized();
	float _dotProduct = _direction.dot(_normalizedNormal);
	return _direction - _normalizedNormal * ((1 + _restitution) * _dotProduct);
}
