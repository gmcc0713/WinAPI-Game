#include "GameManager.h"
namespace ENGINE
{
	void GameManager::Initialize(HWND hWnd, unsigned int width, unsigned int height)
	{
		SceneMgr->Initialize(hWnd, width, height);

		


	}

	void GameManager::Release()
	{
		SceneMgr->Destroy();
	}

	void GameManager::Update()
	{
		SceneMgr->Render();
	}

}