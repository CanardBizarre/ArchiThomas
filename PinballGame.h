#pragma once
#include "Game.h"
class PinballGame : public Game
{
	class Ball* ball;
	class KinematicTrayActor* trajectorie;

public:
	PinballGame();
	virtual ~PinballGame();

protected:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};

