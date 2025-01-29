#include "PinballGame.h"
#include "Ball.h"
#include "Level.h"
#include "InputManager.h"
#include "RectangleActor.h"
#include "KinematicTrayActor.h"

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
	ball = Level::SpawnActor(Ball(10.0f));
	ball->SetPosition(Vector2f(window.getSize().x * 0.3f, window.getSize().y * 0.5f));
	ball->SetAngle(300.0f);
	ball->SetForce(100.0f);

	trajectorie = new KinematicTrayActor(300.0f, 100.0f, ball->GetPosition());
	trajectorie->Construct();

	M_INPUT.BindAction(Code::Space, [&]() { ball->Launch(); });

}

bool PinballGame::Update()
{
	Super::Update();
	trajectorie->Tick(0.0f);

	return IsOver();
}

void PinballGame::Stop()
{
	Super::Stop();
}
