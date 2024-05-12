#pragma once
#include "EngineMecro.h"
#include "Singleton.h"
#include "Player.h"
namespace ENGINE
{
	class GameManager : public Singleton<GameManager>
	{
	private:
		GameManager() {}

		
	public:
		~GameManager() {}
		void Update();
		void Release();
		void Initialize(HWND hWnd, unsigned int width, unsigned int height);

		int GetDrawSizeX() { return  m_PlayerSr->GetDrawSize().cx; }

		friend Singleton;
	};
#define GameMgr GameManager::GetInstance()
}

