#pragma once
#include "Actor.h"
#include "KinematicsComponent.h"
class KinematicTrayActor : public Actor
{
	float time;
	float angle;
	float power;
	vector<CircleShape*> trajectorie;
	vector<Vector2f> trajectorieCoords;
	KinematicsComponent* movement;


public:
	KinematicTrayActor(const float _angle, const float _power, Vector2f _initialPosition, const float _time = 3.0f);
	KinematicTrayActor(const KinematicTrayActor& _other);
	~KinematicTrayActor();

private:
	void InitTrajectorie();

public:
	virtual void Construct() override;
	virtual void Tick(const float _deltaTime) override;

	void ComputeTrajectorie();
	void DisplayTrajectorie();

};

