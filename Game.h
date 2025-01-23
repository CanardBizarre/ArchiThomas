#pragma once
#include "Singleton.h"
#include "Actor.h"

class MusicSample;
class CameraActor;
class Duck;

class Game : public Singleton<Game>
{
	RenderWindow window;
	using OnRenderWindow = function<void(RenderWindow&)>;
	map<u_int, OnRenderWindow> onRenderWindow;

	//TODO remove
	MusicSample* music;
	CameraActor* camera;
	Duck* duck;
	vector<Duck*> duckList;


	Vector2f center;
	class CircleActor* circle;
	float angle;

public:
	FORCEINLINE u_int BindOnRenderWindow(OnRenderWindow _callback)
	{
		u_int _id = GetUniqueID();
		onRenderWindow.insert({ _id, _callback});
		return _id;
	}
	FORCEINLINE void UnbindOnRenderWindow(const u_int& _uniqueId)
	{
		onRenderWindow.erase(_uniqueId);
	}
	FORCEINLINE void SetView(const View& _view)
	{
		window.setView(_view);
	}
	FORCEINLINE void RemoveView()
	{
		window.setView(window.getDefaultView());
	}

public:
	Game();

protected:
	virtual void Start();
	virtual void Update();
	virtual void Stop();

public:
	virtual void Launch();
	void UpdateWindow();

	//TODO remove
	Duck* RetrieveFirstDuck();
};