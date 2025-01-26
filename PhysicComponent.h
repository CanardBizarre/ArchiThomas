#pragma once

#include "Component.h"

class PhysicComponent : public Component
{
	// Movement
	bool canMove;
	float moveSpeed;
	Vector2f direction;

	//Fall
	float gravity;
	float mass;

	Vector2f bounceOffset;
public:
	FORCEINLINE void SetCanMove(const bool _status)
	{
		canMove = _status;
	}
	FORCEINLINE void SetDirection(const Vector2f _direction)
	{
		bounceOffset = _direction;
	}
	

public:
	PhysicComponent(Actor* _owner, const float _moveSpeed, const Vector2f _direction, const float _mass);
	PhysicComponent(Actor* _owner, const PhysicComponent* _other);

private:
	Vector2f ComputeRebound(const Vector2f& _direction, const Vector2f& _normal, float _restitution);
protected:
	virtual void Tick(const float _deltaTime) override;
public:
	void ApplyBounce();
	void DEBUG();
};

