#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Plunger : public MeshActor
{
	//MovementComponent* movement;
	AnimationComponent* animation;

public:
	//FORCEINLINE MovementComponent* GetMovement()
	//{
	//	return movement;
	//}
public:
	Plunger(const Vector2f& _size, const string& _path = "", const IntRect& _rect = {});
	Plunger(const Plunger& _other);

protected:
	virtual void BeginPlay() override;
public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
};