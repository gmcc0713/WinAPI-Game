#include "TimeManager.h"

namespace ENGINE
{

	VOID TimeManager::Initialize(UINT32 FPS)
	{
		this->FPS = 1000 / FPS;
		currTime = lastTime = GetTickCount64();
		m_fGametime = 0;
	}

	BOOL TimeManager::Update()
	{
		currTime = GetTickCount64();
		elapsed = (currTime - lastTime);
		m_fGametime += elapsed;
		if (elapsed < FPS) return FALSE;		//�ҿ�� �ð��� FPS���� ������? 

		elapseTime = elapsed * 0.001f;		//�ҿ�� �ð��� FPS���� Ŭ�� 
		lastTime = currTime;

		return TRUE;
	}
}