#pragma once
#include "Game.h"
#include "MeshActor.h"
#include "MusicSample.h"
#include "Duck.h"

class MusicSample;
class CameraActor;
class Duck;

class DuckHuntGame : public Game
{
	MeshActor* background;
	MusicSample* music;
	CameraActor* camera;
	Duck* duck;
	vector<Duck*> duckList;
	Vector2f center;
	class CircleActor* circle;
	float angle;


	class Ball* ball;
	class MeshActor* floor;
public:
	DuckHuntGame();
	virtual ~DuckHuntGame();

protected:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

public:

	//TODO remove
	Duck* RetrieveFirstDuck();
};