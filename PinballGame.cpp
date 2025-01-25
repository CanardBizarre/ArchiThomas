#include "PinballGame.h"
#include "Ball.h"
#include "Level.h"
#include "InputManager.h"

PinballGame::PinballGame() : Game()
{
	ball = nullptr;
}

PinballGame::~PinballGame()
{
}

void PinballGame::Start()
{
	Super::Start();
	ball = Level::SpawnActor(Ball(25.0f));
	ball->SetOriginAtMiddle();
	ball->SetPosition(Vector2f(window.getSize().x * 0.10f, window.getSize().y * 0.70f));
	
	ball->SetAngle(320.0f);
	ball->SetForce(50.0f);
	M_INPUT.BindAction(Code::Space, [&]() { ball->Launch(); });
}

bool PinballGame::Update()
{
	Super::Update();
	return IsOver();
}

void PinballGame::Stop()
{
	Super::Stop();
}
