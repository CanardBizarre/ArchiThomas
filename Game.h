#pragma once
#include "CoreMinimal.h"

class Game
{
protected:
	RenderWindow window;

public:
	FORCEINLINE Vector2u GetWindowSize() const
	{
		return window.getSize();
	}

	FORCEINLINE virtual bool IsOver() const
	{
		return !window.isOpen();
	}

public:
	 Game();
	 virtual ~Game();
public:
	virtual void Start();
	virtual bool Update();
	virtual void Stop();

	void UpdateWindow();

};