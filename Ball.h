#pragma once
#include "MeshActor.h"
class Ball : public MeshActor
{
	// Movement
	bool canMove;
	float moveSpeed;
	Vector2f direction;

	//Fall
	float gravity;
	float mass;
	Vector2f offset;
	float time;

	Vector2f bounceOffset;

	Vector2f fallMovement;
public:
	FORCEINLINE void SetCanMove(const bool _status)
	{
		canMove = _status;
	}
	FORCEINLINE void SetDirection(const Vector2f _direction)
	{
		bounceOffset = _direction;
	}
	FORCEINLINE Vector2f GetDirection()const 
	{
		return fallMovement;
	}
	FORCEINLINE void ApplyBounce()
	{
		// Bounce
		const Vector2f _normal = Vector2f(0.0f, -1.0f);
		Move(Vector2f(_normal));
		bounceOffset = ComputeRebound(bounceOffset, _normal, 0.8f);
		fallMovement = Vector2f();
		time = 0.0f;
	}
public:
	Ball(const float _radius);

private:
	Vector2f ComputeRebound(const Vector2f& _direction, const Vector2f& _normal, float _restitution);
public:
	virtual void Tick(const float _deltaTime)override;
	void DEBUG();
};

