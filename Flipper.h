#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"

struct ActionState
{
	function<void()> callback; // La fonction à exécuter
	bool state;                     // L'état associé à l'action
};

class Flipper : public MeshActor
{
	//MovementComponent* movement;
	bool isLeftFlipper;
public:
	Flipper(const Vector2f& _size, const string& _path = "", const bool _isLeftFlipper = true, const IntRect& _rect = {});
	Flipper(const Flipper& _other);

protected:
	virtual void BeginPlay() override;
public:
	virtual void Construct() override;
	virtual void Deconstruct() override;

private:
	void ActiveFlipper();
};