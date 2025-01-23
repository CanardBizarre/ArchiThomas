#include "CameraActor.h"
#include "Game.h"
#include "Duck.h"

CameraActor::CameraActor() : Actor("Camera")
{
	camera = CreateComponent<CameraComponent>();
	target = nullptr;
}

CameraActor::CameraActor(const Vector2f& _center, const Vector2f& _size) : Actor("Camera")
{
	camera = CreateComponent<CameraComponent>(_center, _size);
	target = nullptr;
}

CameraActor::CameraActor(const FloatRect& _rect) : Actor("Camera")
{
	camera = CreateComponent<CameraComponent>(_rect);
	target = nullptr;
}

CameraActor::CameraActor(const CameraActor& _other) : Actor(_other)
{
	camera = CreateComponent<CameraComponent>(_other.camera);
	target = nullptr; //TODO check
}

void CameraActor::Construct()
{
	Super::Construct();
	M_GAME.SetView(*camera->GetView());
}

void CameraActor::Deconstruct()
{
	Super::Deconstruct();
	M_GAME.RemoveView();
}


void CameraActor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (!target) return;
	if (target->IsToDelete())
	{
		SetTarget(M_GAME.RetrieveFirstDuck());
		if (!target) return;
	}

	SetPosition(target->GetPosition());
}