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

    // Plateau de jeu
    gameBoard = _createActor(Vector2f(800, 900), "Pinball/Background", _gameBoardPosition);

    // Murs
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _wallData = 
    {
        {Vector2f(720, 200), "Pinball/Flipper_Bottom", Vector2f(100.0f, 750.0f), false, 0.0f},
        {Vector2f(200, 60), "Pinball/Wall_1", Vector2f(650.0f, 715.0f), true, 0.0f},//
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
        Flipper* _flipper = Level::SpawnActor(Flipper(Vector2f(100, 50), "Pinball/Flipper_" + to_string(_index + 1)));
        _flipper->SetOriginAtMiddle();
        Vector2f _flipperPosition = (_index == 0)
            ? Vector2f(_gameBoardPosition.x + 15, _gameBoardPosition.y + 250)
            : Vector2f(_gameBoardPosition.x - 125, _gameBoardPosition.y + 250);
        _flipper->SetPosition(_flipperPosition);
        flippers.push_back(_flipper);
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