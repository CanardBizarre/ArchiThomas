#pragma once
#include "MovementComponent.h"
class KinematicsComponent :  public MovementComponent
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
	FORCEINLINE void ResetTimer()
	{
		time = 0;
	}

public:
	KinematicsComponent(Actor* _owner, const float _angle = 0.0f, const float _power = 0.0f);

	KinematicsComponent(Actor* _owner, KinematicsComponent* _other);

public:
	void Lauch();
	virtual void Move(const float _delta) override;
	Vector2f ComputeNewCoordinate(const float _delta);

};

