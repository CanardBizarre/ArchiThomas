#include "PinballGame.h"
#include "Level.h"
#include "Flipper.h"
#include "Plunger.h"
#include "Label.h"
#include "MusicSample.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"

PinballGame::PinballGame()
{
    
}

PinballGame::~PinballGame()
{
    delete score;
}

void PinballGame::GenerateScore(const Vector2f& _pos)
{
    // Création des éléments

    const string& _labelText = "Score :";
    score = new Label(_labelText, "Cheese_Market", OTF);
    score->SetPosition(Vector2f(_pos.x - _labelText.size(), _pos.y));
}

void PinballGame::GenerateGameBoard(const Vector2f& _pos, const Vector2f& _size)
{
    // Plateau de jeu
    gameBoard = CreateActors(_size, "Pinball/Background", _pos);
}

void PinballGame::GeneratePlunger(const Vector2f& _pos, const Vector2f& _size)
{
    // Plunger
    plunger = Level::SpawnActor(Plunger(_size, "Pinball/Plunger"));
    plunger->SetPosition(_pos);
}

void PinballGame::GenerateWalls()
{
    // Murs
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _wallData =
    {
        {Vector2f(720, 200), "Pinball/Flipper_Bottom", Vector2f(100.0f, 750.0f), false, 0.0f},
        {Vector2f(200, 60), "Pinball/Wall_1", Vector2f(660.0f, 715.0f), true, 0.0f},
        {Vector2f(200, 60), "Pinball/Wall_2", Vector2f(230.0f, 715.0f), true, 0.0f},
        {Vector2f(60, 100), "Pinball/Blocker", Vector2f(280.0f, 250.0f), true, -30.0f},
        {Vector2f(60, 100), "Pinball/Blocker", Vector2f(650.0f, 250.0f), true, 30.0f}
    };
    for (const auto [_size, _texture, _position, _useMiddleOrigin, _rotation] : _wallData)
    {
        walls.push_back(CreateActors(_size, _texture, _position, _useMiddleOrigin, _rotation));
    }
}

void PinballGame::GenerateSlingshots()
{
    // Limites 
    vector<tuple<Vector2f, string, Vector2f, bool>> _slingshots =
    {
         {Vector2f(120, 120), "Pinball/Slingshot_1", Vector2f(680.0f, 580.0f), true},
         {Vector2f(120, 120), "Pinball/Slingshot_2", Vector2f(250.0f, 580.0f), true},
         {Vector2f(220, 80), "Pinball/Slingshot_3", Vector2f(480.0f, 350.0f), true},
    };
    for (const auto [_size, _texture, _position, _useMiddleOrigin] : _slingshots)
    {
        slingshots.push_back(CreateActors(_size, _texture, _position, _useMiddleOrigin));
    }
}

void PinballGame::GenerateBumpers()
{
    // Bumpers
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _bumpers =
    {
        { Vector2f(110, 60), "Pinball/Bumper_25", Vector2f(380.0f, 120.0f), true, 25.0f },
        { Vector2f(110, 60), "Pinball/Bumper_100", Vector2f(580.0f, 120.0f), true, 100.0f },
        { Vector2f(110, 60), "Pinball/Bumper_50", Vector2f(480, 200.0f), true, 50.0f }
    };
    u_int _index = 0;
    for (const auto [_size, _texture, _position, _useMiddleOrigin, _scorePoint] : _bumpers)
    {
        bumpers.push_back(CreateActors<Bumper>(_size, _texture, _position, _useMiddleOrigin));
        bumpers[_index++]->SetScorePoint(_scorePoint);
    }
}

void PinballGame::GenerateFlippers(const Vector2f& _size)
{
    // Flippers
    for (u_int _index = 0; _index < 2; ++_index)
    {
        Flipper* _flipper = Level::SpawnActor(Flipper(_size, "Pinball/Flipper_" + to_string(_index + 1), _index == 1));
        if (_index == 1) {
            _flipper->SetOrigin(Vector2f(0, 25));  // Origine en haut à gauche pour le flipper de gauche
        }
        else {
            _flipper->SetOrigin(Vector2f(100, 25)); // Origine en haut à droite pour le flipper de droite
        }

        Vector2f _flipperPosition = (_index == 0)
            ? Vector2f(gameBoard->GetPosition().x + 70, gameBoard->GetPosition().y + 250)
            : Vector2f(gameBoard->GetPosition().x - 180, gameBoard->GetPosition().y + 250);
        _flipper->SetPosition(_flipperPosition);
        flippers.push_back(_flipper);
    }
}

void PinballGame::GenerateActors()
{
    GenerateScore(Vector2f(500, 10));
    GenerateGameBoard(Vector2f(500.0f, 500.0f), Vector2f(800, 900));
    GeneratePlunger(Vector2f(820.0f, 850.0f), Vector2f(87.0f, 150.0f));
    GenerateWalls();
    GenerateSlingshots();
    GenerateBumpers();
    GenerateFlippers(Vector2f(100, 50));
}

void PinballGame::Start()
{
	Super::Start();

    new Timer([&](){ M_AUDIO.PlaySample<MusicSample>("GodzillaSoundtrack"); }, seconds(5), true, false);

    M_AUDIO.PlaySample<MusicSample>("BackgroundEffect_3");

    new Timer([&]() 
    {
        const u_int& _result = GetRandomNumberInRange(0, 2);
        switch (_result)
        {
        case 0:
            M_AUDIO.PlaySample<MusicSample>("BackgroundEffect_1");
            break;
        case 1:
            M_AUDIO.PlaySample<MusicSample>("BackgroundEffect_2");
            break;
        case 2:
            M_AUDIO.PlaySample<MusicSample>("BackgroundEffect_3");
            break;
        default:
            break;
        }
    }, seconds(120), true, true);
    
    GenerateActors();  
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