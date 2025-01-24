#pragma once
#include "Singleton.h"
#include "Game.h"
class GameManager :  public Singleton<GameManager>
{
	Game* current;

public:
	~GameManager();

public:
	FORCEINLINE Game* GetCurrent()
	{
		return current; 
	}

public:
	void Launch(Game* _currentGame);

};

