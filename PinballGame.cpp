#include "PinballGame.h"
#include "Level.h"
#include "Flipper.h"

PinballGame::PinballGame()
{

}

PinballGame::~PinballGame()
{

}

void PinballGame::Start()
{
	Super::Start();
	const float _sizeX = window.getSize().x;
	const float _sizeY = window.getSize().y;
	const Vector2f _position = Vector2f(500.0f, 500.0f);
    gameBoard = Level::SpawnActor(MeshActor(Vector2f(800, 900), "Pinball/Background"));
    gameBoard->SetOriginAtMiddle();
    gameBoard->SetPosition(_position);

	for (u_int _index = 0; _index < 2; _index++)
	{
		flippers.push_back(Level::SpawnActor(Flipper(Vector2f(100, 50), "Pinball/Flipper_" + to_string(_index + 1))));
		flippers[_index]->SetOriginAtMiddle();
		if (_index == 0)
		{
			flippers[_index]->SetPosition(Vector2f(_position.x, _position.y + 250));
		}
		else
		{
			flippers[_index]->SetPosition(Vector2f(_position.x - 125, _position.y + 250));
		}
	}
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