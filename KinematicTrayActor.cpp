#include "KinematicTrayActor.h"
#include "GameManager.h"

KinematicTrayActor::KinematicTrayActor(const float _angle, const float _power, Vector2f _initialPosition, const float _time)
	:Actor("KinematicActor")
{
	angle = _angle;
	power = _power;
	time = _time;
	SetPosition(_initialPosition);
	movement = CreateComponent<KinematicsComponent>(_angle, _power);
}

KinematicTrayActor::KinematicTrayActor(const KinematicTrayActor& _other)
{
	angle = _other.angle;
	power = _other.power;
	time = _other.time;
	SetPosition(_other.GetPosition());
	trajectorieCoords = _other.trajectorieCoords;
	trajectorie = _other.trajectorie;
	movement = CreateComponent<KinematicsComponent>(_other.movement);
}

KinematicTrayActor::~KinematicTrayActor()
{
	for (CircleShape* _dot : trajectorie)
	{
		delete _dot;
	}
}

void KinematicTrayActor::Construct()
{
	Super::Construct();
	InitTrajectorie();
}

void KinematicTrayActor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	ComputeTrajectorie();
	DisplayTrajectorie();
}

void KinematicTrayActor::InitTrajectorie()
{
	for (u_int _index = 0; _index < 15; _index++)
	{
		CircleShape* _newDot = new CircleShape(100.0f);
		_newDot->setFillColor(sf::Color(150, 50, 250));
		trajectorie.push_back(_newDot);
	}

}

void KinematicTrayActor::ComputeTrajectorie()
{
	movement->ResetTimer();
	for (CircleShape* _dot : trajectorie)
	{
		Vector2f _newCoordinate = movement->ComputeNewCoordinate(time);
		_dot->setPosition(_newCoordinate);
	}
}

void KinematicTrayActor::DisplayTrajectorie()
{
	for (CircleShape* _dot : trajectorie)
	{
		M_GAME.GetCurrent()->GetRenderWindow().draw(*_dot);
	}
}
