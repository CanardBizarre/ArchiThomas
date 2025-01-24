#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"

class Cloud : public MeshActor
{
	MovementComponent* movement;
public:
	FORCEINLINE MovementComponent* GetMovement()
	{
		return movement;
	}
public:
	Cloud(const Vector2f& _size, const string& _path = "", const IntRect& _rect = {});
	Cloud(const Cloud& _other);

public:
	virtual void BeginPlay() override;
};

