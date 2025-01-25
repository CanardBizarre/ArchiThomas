#include "Flipper.h"

Flipper::Flipper(const Vector2f& _size, const string& _path, const IntRect& _rect) : MeshActor(_size, _path, PNG, _rect, "Flipper")
{
	movement = CreateComponent<MovementComponent>();
}

Flipper::Flipper(const Flipper& _other) : MeshActor(_other)
{
	movement = CreateComponent<MovementComponent>(_other.movement);
}

void Flipper::BeginPlay()
{

}

void Flipper::Construct()
{
	Super::Construct();
}

void Flipper::Deconstruct()
{
	Super::Deconstruct();
}
