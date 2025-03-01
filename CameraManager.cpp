#include "CameraManager.h"

Camera::CameraManager::CameraManager()
{
	CreateCamera("Default");
}

void Camera::CameraManager::RenderAllCamera(RenderWindow& _window)
{
	for (const pair<string, CameraActor*>& _cameraPair : allCameras)
	{
		_window.setView(*_cameraPair.second->GetView());

		for (const pair<u_int, OnRenderWindow>& _renderPair : onRenderWindow)
		{
			_renderPair.second(_window);
		}

	}
	_window.setView(_window.getDefaultView());
	
}

