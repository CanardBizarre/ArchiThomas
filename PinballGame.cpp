#include "PinballGame.h"
#include "Level.h"
#include "Flipper.h"
#include "Plunger.h"
#include "Label.h"
#include "MusicSample.h"
#include "AudioManager.h"
#include "CameraManager.h"

PinballGame::PinballGame()
{
    scoreLabel = nullptr;
    score = 0;
    background = nullptr;
    gameBoard = nullptr;
    plunger = nullptr;
    flippers = vector<Flipper*>();
    bounds = vector<MeshActor*>();
    walls = vector<MeshActor*>();
}

PinballGame::~PinballGame()
{
    delete scoreLabel;
}

void PinballGame::Start()
{
	Super::Start();

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

    auto _createActor = [](const Vector2f& _size, const string& _texture, const Vector2f& _position, bool _useMiddleOrigin = true, float _rotation = 0.0f) 
    {
        MeshActor* _actor = Level::SpawnActor(MeshActor(_size, _texture));
        if (_useMiddleOrigin) 
        {
            _actor->SetOriginAtMiddle();
        }
        _actor->SetPosition(_position);
        if (_rotation != 0.0f) 
        {
            _actor->Rotate(degrees(_rotation));
        }
        return _actor;
    };

    // Création des éléments
    const Vector2f _gameBoardPosition(500.0f, 500.0f);

    const string& _labelText = "Score :";
    scoreLabel = new Label(_labelText, "Cheese_Market", OTF);
    scoreLabel->SetPosition(Vector2f(500 - _labelText.size(), 10));
    
    // Plateau de jeu
    gameBoard = _createActor(Vector2f(800, 900), "Pinball/Background", _gameBoardPosition);

    plunger = Level::SpawnActor(Plunger(Vector2f(87.0f, 150.0f), "Pinball/Plunger"));
    plunger->SetPosition(Vector2f(820.0f, 850.0f));


    // Murs
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _wallData = 
    {
        {Vector2f(720, 200), "Pinball/Flipper_Bottom", Vector2f(100.0f, 750.0f), false, 0.0f},
        {Vector2f(200, 60), "Pinball/Wall_1", Vector2f(660.0f, 715.0f), true, 0.0f},//
        {Vector2f(200, 60), "Pinball/Wall_2", Vector2f(230.0f, 715.0f), true, 0.0f},//
        {Vector2f(60, 100), "Pinball/Blocker", Vector2f(280.0f, 250.0f), true, -30.0f},
        {Vector2f(60, 100), "Pinball/Blocker", Vector2f(650.0f, 250.0f), true, 30.0f}
    };

    for (const auto& [_size, _texture, _position, _useMiddleOrigin, _rotation] : _wallData) 
    {
        walls.push_back(_createActor(_size, _texture, _position, _useMiddleOrigin, _rotation));
    }

    // Limites et bumpers
    vector<tuple<Vector2f, string, Vector2f, bool>> _boundData = 
   {
        {Vector2f(120, 120), "Pinball/Slingshot_1", Vector2f(680.0f, 580.0f), true},
        {Vector2f(120, 120), "Pinball/Slingshot_2", Vector2f(250.0f, 580.0f), true},
        {Vector2f(220, 80), "Pinball/Slingshot_3", Vector2f(480.0f, 350.0f), true},
        {Vector2f(110, 60), "Pinball/Bumper_25", Vector2f(380.0f, 120.0f), true},
        {Vector2f(110, 60), "Pinball/Bumper_100", Vector2f(580.0f, 120.0f), true},
        {Vector2f(110, 60), "Pinball/Bumper_50", Vector2f(480, 200.0f), true}
    };

    for (const auto& [_size, _texture, _position, _useMiddleOrigin] : _boundData) 
    {
        bounds.push_back(_createActor(_size, _texture, _position, _useMiddleOrigin));
    }

    // Flippers
    for (u_int _index = 0; _index < 2; ++_index) 
    {
        Flipper* _flipper = Level::SpawnActor(Flipper(Vector2f(100, 50), "Pinball/Flipper_" + to_string(_index + 1), _index == 1));
        if (_index == 1) {
            _flipper->SetOrigin(Vector2f(0, 25));  // Origine en haut à gauche pour le flipper de gauche
        }
        else {
            _flipper->SetOrigin(Vector2f(100, 25)); // Origine en haut à droite pour le flipper de droite
        }

        Vector2f _flipperPosition = (_index == 0)
            ? Vector2f(_gameBoardPosition.x + 70, _gameBoardPosition.y + 250)
            : Vector2f(_gameBoardPosition.x - 180, _gameBoardPosition.y + 250);
        _flipper->SetPosition(_flipperPosition);
        flippers.push_back(_flipper);
    }

    CameraActor* _camera = new CameraActor({500.0f, 500.0f}, Vector2f({ 500.0f, 500.0f }));
    M_CAMERA.Register(_camera);
    M_CAMERA.SetCurrent(_camera);
    //_camera->BeginPlay();
}

bool PinballGame::Update()
{
	Super::Update();
    LOG(Display, "- Score : " + to_string(score));


	return IsOver();
}

void PinballGame::Stop()
{
	Super::Stop();
}