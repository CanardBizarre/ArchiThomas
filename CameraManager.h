#pragma once
#include "Singleton.h"
#include "CameraActor.h"
#include "Level.h"
namespace Camera
{
	class CameraManager : public Singleton<CameraManager>
	{
		using OnRenderWindow = function<void(RenderWindow&)>;
		map<u_int, OnRenderWindow> onRenderWindow;
		map<string, CameraActor*> allCameras;
		CameraActor* current;

	public:
		FORCEINLINE CameraActor* GetCurrent()const 
		{
			return current;
		}
		FORCEINLINE CameraActor* GetCameraByName(const string& _cameraName)const
		{
			if (!allCameras.contains(_cameraName))return nullptr;
			return allCameras.at(_cameraName);
		}
		FORCEINLINE u_int BindOnRenderWindow(OnRenderWindow _callback)
		{
			u_int _id = GetUniqueID();
			onRenderWindow.insert({ _id, _callback });
			return _id;
		}
		FORCEINLINE void UnbindOnRenderWindow(const u_int& _uniqueId)
		{
			onRenderWindow.erase(_uniqueId);
		}
		FORCEINLINE void SetCurrent(CameraActor* _current)
		{
			current = _current;
		}

		FORCEINLINE void Register(CameraActor* _camera)
		{
			if (!_camera)return;
			allCameras.insert({ _camera->GetDisplayName(), _camera });
		}

		FORCEINLINE void RemoveCamera(const string& _cameraName)
		{
			allCameras.erase(_cameraName);
		}



	public:
		CameraManager();

		template<typename Type = CameraActor, IS_BASE_OF(CameraActor, Type)>
		Type* CreateCamera(const string& _name = "Camera")
		{
			Type* _camera = Level::SpawnActor(Type(_name));
			if (!current)
			{
				Register(_camera);
				SetCurrent(_camera);
			}
			return _camera;
		}

		void RenderAllCamera(RenderWindow& _window);

	};
}

using namespace Camera;
