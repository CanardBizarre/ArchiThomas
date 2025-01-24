#include "CameraActor.h"
#include "GameManager.h"
#include "DuckHuntGame.h"
#include "Duck.h"

CameraActor::CameraActor(const string& _name) : Actor("Camera")
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
}

void CameraActor::Deconstruct()
{
	Super::Deconstruct();
}


void CameraActor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (!target) return;
	if (target->IsToDelete())
	{
		if(Game* _game = M_GAME.GetCurrent())
		SetTarget(Cast<DuckHuntGame>(_game)->RetrieveFirstDuck());
		if (!target) return;
	}

	SetPosition(target->GetPosition());
}