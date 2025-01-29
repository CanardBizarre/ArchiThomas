#pragma once
#include "MeshActor.h"
#include "KinematicsComponent.h"
class Ball : public MeshActor
{
	KinematicsComponent* movement;

public:
	FORCEINLINE KinematicsComponent* GetMovement()
	{
		return movement;
	}
	FORCEINLINE void Launch()
	{
		movement->Lauch();
	}

	FORCEINLINE void SetForce(const float _force)
	{
		movement->SetPower(_force);
	}
	FORCEINLINE void SetAngle(const float _angle)
	{
		movement->SetAngle(_angle);
	}

public:
	Ball(const float _radius);
	Ball(const Ball& _other);

public:
	virtual void Tick(const float _deltaTime)override;
};

