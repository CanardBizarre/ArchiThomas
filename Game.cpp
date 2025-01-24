#include "Game.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"

Game::Game()
{
	window = RenderWindow();
}

Game::~Game()
{
}

void Game::Start()
{
    window.create(VideoMode({800, 800}), "SFML works!");
};

bool Game::Update()
{
	
    TM_Seconds& _timer = M_TIMER;
    _timer.Update();

    while (const optional _event = window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            window.close();
        }
    }
    const float _deltaTime = _timer.GetDeltaTime().asSeconds();
    M_ACTOR.Tick(_deltaTime);

    static float _t = _deltaTime;

    float _value = Lerp(0.0f,100.0f, _t);
    _t += _deltaTime;

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
