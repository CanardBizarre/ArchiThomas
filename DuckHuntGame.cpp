#include "DuckHuntGame.h"
#include "Level.h"
#include "TimerManager.h"
#include "CircleActor.h"
#include "CameraManager.h"
#include "Ball.h"


DuckHuntGame::DuckHuntGame() : Game()
{
	
}

DuckHuntGame::~DuckHuntGame()
{
	
}


void DuckHuntGame::Start()
{
	Super::Start();
	LOG(Display, "DuckHuntGame::Start");


	const float _x = window.getSize().y * 0.2f;
	floor = Level::SpawnActor(MeshActor(Vector2f(window.getSize().x, window.getSize().y * 0.2f)));
	const float _posX = 0.0f;
	const float _posY = window.getSize().y * 0.8f;
	floor->SetPosition({ _posX , _posY });
	

	ball = Level::SpawnActor(Ball(50.0f));
	ball->SetOriginAtMiddle();
	ball->SetPosition(Vector2f(window.getSize()) / 2.0f);

	


}

bool DuckHuntGame::Update()
{
	Super::Update();
	Shape* _ballShape = ball->GetMesh()->GetShape()->GetDrawable();
	const FloatRect& _ballRect = _ballShape->getGlobalBounds();

	Shape* _floorShape = floor->GetMesh()->GetShape()->GetDrawable();
	const FloatRect& _floorRect = _floorShape->getGlobalBounds();
	
	
	return IsOver();
}

void DuckHuntGame::Stop()
{
	Super::Stop();
	LOG(Display, "DuckHuntGame::Stop");
}



Duck* DuckHuntGame::RetrieveFirstDuck()
{
	if (duckList.empty()) return nullptr;

	const vector<Duck*>::iterator& _it = duckList.begin();
	Duck* _duck = *_it;
	duckList.erase(_it);

	return _duck;
}