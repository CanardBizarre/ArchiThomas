#include "DuckHuntGame.h"
#include "Level.h"
#include "TimerManager.h"

DuckHuntGame::DuckHuntGame() : Game()
{
	//background = new MeshActor();
	duck = nullptr;
}

DuckHuntGame::~DuckHuntGame()
{
	delete background;
}


void DuckHuntGame::Start()
{
	Super::Start();

	//Level::SpawnActor(MeshActor(Vector2f(463.0f, 260.0f) * 2.0f, "background", JPG));
	Level::SpawnActor(MeshActor(Vector2f(50.0f, 50.0f), "duck"));

	/*new Timer([&]() 
		{
			Level::SpawnActor(MeshActor(Vector2f(50.0f, 50.0f), "duck"));
		},
		seconds(1.0f),
		true,
		true
	);*/

	LOG(Display, "DuckHuntGame::Start");
}

void DuckHuntGame::Update()
{
	Super::Update();
	LOG(Display, "DuckHuntGame::Update");
}

void DuckHuntGame::Stop()
{
	Super::Stop();
	LOG(Display, "DuckHuntGame::Stop");
}


void DuckHuntGame::Launch()
{
	Start();
	Update();
	Stop();
}