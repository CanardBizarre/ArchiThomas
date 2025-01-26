#include "Game.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"
#include "InputManager.h"

Game::Game()
{
	window = RenderWindow();
}

Game::~Game()
{
}

void Game::Start()
{
    window.create(VideoMode({1000, 1000}), "SFML works!");
};

bool Game::Update()
{
	
    TM_Seconds& _timer = M_TIMER;
    _timer.Update();
    M_INPUT.ConsumeData(window);
    const float _deltaTime = _timer.GetDeltaTime().asSeconds();
    M_ACTOR.Tick(_deltaTime);

    return IsOver();
}

void Game::UpdateWindow()
{
    window.clear();
    M_CAMERA.RenderAllCamera(window);
    window.display();
}


void Game::Stop()
{
    M_ACTOR.BeginDestroy();
}
