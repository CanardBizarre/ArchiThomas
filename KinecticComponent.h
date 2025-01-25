#pragma once
#include "MovementComponent.h"
class KinecticComponent :  public MovementComponent
{
	float angle;
	float power;

	Vector2f initialVelocity;
	Vector2f initialPosition;
	float time;
	bool isLauched;

public:
	FORCEINLINE void SetAngle(const float _angle)
	{
		angle = _angle;
	}
	FORCEINLINE void SetPower(const float _power)
	{
		power = _power;
	}

public:
	KinecticComponent(Actor* _owner);
	KinecticComponent(Actor* _owner, KinecticComponent* _other);

public:
	void Lauch();
	virtual void Move(const float _delta) override;


};

