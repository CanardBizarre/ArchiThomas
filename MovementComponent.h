#pragma once
#include "Component.h"
enum MovementType
{
	MT_MOVE,
	MT_ROTATEAROUND,
	MT_ROTATEAT,
};

class MovementComponent : public Component
{ 
	float speed;
	float rotateSpeed;
	Vector2f direction;
	Actor* target;
	vector<MovementType> movementsAction;
public:

	FORCEINLINE void SetTarget(Actor* _target)
	{
		target = _target;
	}
	FORCEINLINE void SetRotateSpeed(const float _rotateSpeed)
	{
		rotateSpeed = _rotateSpeed;
	}

	MovementComponent(Actor* _owner, vector<MovementType> _movementsAction = {});
	MovementComponent(Actor* _owner, const MovementComponent* _other);

protected:
	virtual void Tick(const float _deltaTime) override;

private:
	void Move(const float _deltaTime);
	void RotateAround(const float _deltaTime);
	void RotateToTarget(const float _deltaTime);
};