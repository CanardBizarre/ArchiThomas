#pragma once
#include "Component.h"

class MovementComponent : public Component
{ 
	float speed;
	float rotateSpeed;
	Vector2f direction;
	Actor* target;

public:

	FORCEINLINE void SetTarget(Actor* _target)
	{
		target = _target;
	}

	MovementComponent(Actor* _owner);
	MovementComponent(Actor* _owner, const MovementComponent* _other);

protected:
	virtual void Tick(const float _deltaTime) override;

private:
	void Move(const float _deltaTime);
	void RotateAround(const float _deltaTime);
};