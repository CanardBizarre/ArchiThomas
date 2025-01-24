#include "GameManager.h"

GameManager::~GameManager()
{
	delete current;
}

void GameManager::Launch(Game* _currentGame)
{
	if (!(current = _currentGame)) return;
	current->Start();
	while(!current->Update());
	current->Stop();

}
