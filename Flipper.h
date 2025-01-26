#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"

class Flipper : public MeshActor
{
	//MovementComponent* movement;

public:
	Flipper(const Vector2f& _size, const string& _path = "", const IntRect& _rect = {});
	Flipper(const Flipper& _other);

protected:
	virtual void BeginPlay() override;
public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
};