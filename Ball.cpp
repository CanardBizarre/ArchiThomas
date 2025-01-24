#include "Ball.h"

Ball::Ball(const float _radius) : MeshActor(_radius, 30, "PopCat")
{
	// Movement
	canMove = true;
	moveSpeed = 5.0f;

	// Fall
	mass = 20.0f;
	gravity = 9.81f;
	direction = Vector2f();
	bounceDuration = 0.5f;
	EaseOutQuart(bounceDuration);
	fallMovement = Vector2f();
}


void Ball::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	
	if (canMove)
	{
		// Direciton
		const Vector2f& _directionOffset = direction * moveSpeed * 100.0f;

		// Fall
		const Vector2f _downVector = Vector2f(0.0f, 1.0f);
		const Vector2f _fallOffset = _downVector * gravity * mass;

		// Bounce
		if (bounceDuration != 0.0f)
		{
			bounceDuration -= _deltaTime;
			bounceDuration = bounceDuration < 0.0f ? 0.0f : bounceDuration;
			bounceDirection *= EaseOutQuart(1.0f);
		}


		// Result
		const Vector2f& _offset = _directionOffset + bounceDirection + _fallOffset;
		fallMovement += _fallOffset * _deltaTime;
		Move(_offset * _deltaTime);
	}
	
}

Vector2f Ball::ComputeRebound(const Vector2f& _direction, const Vector2f& _normal, float _restitution)
{
	Vector2f _normalizedNormal = _normal.normalized();
	float _dotProduct = _direction.dot(_normalizedNormal);
	return _direction - _normalizedNormal * ((1 + _restitution) * _dotProduct);
}
