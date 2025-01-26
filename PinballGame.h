#pragma once
#include "Game.h"
#include "MeshActor.h"

class Flipper;
class Plunger;

class PinballGame : public Game
{
	//Game background
	MeshActor* background;
	MeshActor* gameBoard;
	Plunger* plunger;
	//Balle du flipper
	//Ball* ball;
	//Flipper droit + gauche
	vector<Flipper*> flippers;
	//Les bounds contre lesquels se cogner
	vector<MeshActor*> bounds;
	vector<MeshActor*> walls;

public:
	PinballGame();
	~PinballGame();

protected:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};

