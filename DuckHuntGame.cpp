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


	floor = Level::SpawnActor(MeshActor(Vector2f(window.getSize().x * 2, window.getSize().y * 0.05f)));
	const float _posX = 0.0f;
	const float _posY = window.getSize().y * 0.99f;
	floor->SetPosition({ _posX , _posY });
	

	ball = Level::SpawnActor(Ball(10.0f));
	ball->SetOriginAtMiddle();
	ball->SetPosition(Vector2f(window.getSize().x / 2.0f, 0.0f));

	


}

bool DuckHuntGame::Update()
{
	Super::Update();
	Shape* _ballShape = ball->GetMesh()->GetShape()->GetDrawable();
	const FloatRect& _ballRect = _ballShape->getGlobalBounds();

	Shape* _floorShape = floor->GetMesh()->GetShape()->GetDrawable();
	const FloatRect& _floorRect = _floorShape->getGlobalBounds();
	
	if (_ballRect.findIntersection(_floorRect))
	{
		ball->ApplyBounce();
		ball->DEBUG();
	}
	//ball->DEBUG();
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