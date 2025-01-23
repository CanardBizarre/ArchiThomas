#pragma once
#include "Game.h"
#include "MeshActor.h"

class DuckHuntGame : public Game
{
	MeshActor* background;
	MeshActor* duck;

public:
	DuckHuntGame();
	~DuckHuntGame();

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Stop() override;

public:
	virtual void Launch() override;
};