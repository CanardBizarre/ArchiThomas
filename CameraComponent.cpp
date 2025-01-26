#include "CameraComponent.h"
#include "GameManager.h"

CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	Vector2u _windowSize = M_GAME.GetCurrent()->GetWindowSize();
	Vector2f _windowSizeFloat = Vector2f(CAST(float, _windowSize.x), CAST(float, _windowSize.y));
	view = new View(_windowSizeFloat / 2.0f, _windowSizeFloat);
}

CameraComponent::CameraComponent(Actor* _owner, const Vector2f& _center, const Vector2f& _size) : Component(_owner)
{
	view = new View(_center, _size);
}

CameraComponent::CameraComponent(Actor* _owner, const FloatRect& _rect) : Component(_owner)
{
	view = new View(_rect);
}

CameraComponent::CameraComponent(Actor* _owner, const CameraComponent* _other) : Component(_owner)
{
	view = new View(*_other->view);
}

CameraComponent::~CameraComponent()
{
	delete view;
}