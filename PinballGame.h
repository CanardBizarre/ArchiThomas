#pragma once
#include "Game.h"
#include "MeshActor.h"
#include "Level.h"
#include "Bumper.h"
class Flipper;
class Plunger;
class Label;
class PinballGame : public Game
{
	Label* score;
	//Game background
	MeshActor* background;
	MeshActor* gameBoard;
	Plunger* plunger;
	//Balle du flipper
	//Ball* ball;
	//Flipper droit + gauche
	vector<Flipper*> flippers;
	//Les bounds contre lesquels se cogner
	vector<MeshActor*> slingshots;
	vector<Bumper*> bumpers;
	vector<MeshActor*> walls;
public:
	PinballGame();
	~PinballGame();
public:
#pragma region Generation
	void GenerateScore(const Vector2f& _pos);
	void GenerateGameBoard(const Vector2f& _pos, const Vector2f& _size);
	void GeneratePlunger(const Vector2f& _pos, const Vector2f& _size);
	void GenerateWalls();
	void GenerateSlingshots();
	void GenerateBumpers();
	void GenerateFlippers(const Vector2f& _size);
	void GenerateActors();
#pragma endregion
	template<typename Type = MeshActor>
	Type* CreateActors(const Vector2f& _size, const string& _texture, const Vector2f& _position,
		bool _useMiddleOrigin = true, float _rotation = 0.0f)
	{
		Type* _actor = Level::SpawnActor(Type(_size, _texture));

		if (_useMiddleOrigin)
		{
			_actor->SetOriginAtMiddle();
		}
		_actor->SetPosition(_position);
		_actor->InitCoords();
		if (_rotation != 0.0f)
		{
			_actor->Rotate(degrees(_rotation));
		}
		return _actor;
	}
protected:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};