#include "PinballGame.h"
#include "Ball.h"
#include "Level.h"
#include "InputManager.h"
#include "RectangleActor.h"

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
	//ball = Level::SpawnActor(Ball(25.0f));
	//ball->SetOriginAtMiddle();
	//ball->SetPosition(Vector2f(window.getSize().x * 0.10f, window.getSize().y * 0.70f));
	//
	//ball->SetAngle(320.0f);
	//ball->SetForce(50.0f);

	rectangle = Level::SpawnActor(RectangleActor({ 300.0f, 400.0f }));
	rectangle->SetOriginAtMiddle();
	rectangle->SetPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	rectangle->InitCoords();
	rectangle->Rotate(degrees(30.0f));
	//const Vector2f& _size = Vector2f(rectangle->GetSize());
	//const float _halfWidth = _size.x / 2.0f;
	//const float _halfLength = _size.y / 2.0f;
	//const Vector2f& _origin = { rectangle->GetPosition().x, rectangle->GetPosition().y };
	//const Vector2f& _oe = Vector2(_origin.x + _halfWidth, _origin.y);
	//const Vector2f& _aCoord = Vector2(_oe.x, _oe.y + _halfLength);
	//const Vector2f& _dCoord = Vector2(_oe.x, _oe.y - _halfLength);
	//const float _angle = 180.0f;
	//const Vector2f& _coordsRoatated = _aCoord.rotatedBy(degrees(_angle));
	//const Vector2f& _cCoord = Vector2(_coordsRoatated.x + rectangle->GetPosition().x * 2.0f, _coordsRoatated.y + rectangle->GetPosition().y * 2.0f);
	//LOG(Warning, "Origin coords is x: " + to_string(_origin.x) + "y: " + to_string(_origin.y));
	//LOG(Warning, "OE coords is x: " + to_string(_oe.x) + "y: " + to_string(_oe.y));
	//LOG(Warning, "Half width is: " + to_string(_halfWidth));
	//LOG(Warning, "Half length is: " + to_string(_halfLength));
	//LOG(Warning, "A coords is x: " + to_string(_aCoord.x) + "y: " + to_string(_aCoord.y));
	//LOG(Warning, "c coords is x: " + to_string(_cCoord.x) + "y: " + to_string(_cCoord.y));
	//LOG(Warning, "d coords is x: " + to_string(_dCoord.x) + "y: " + to_string(_dCoord.y));

	

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
