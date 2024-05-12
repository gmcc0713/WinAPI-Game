#pragma once
#include "Singleton.h"
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
#endif // !TIME_MANAGER_H
namespace ENGINE
{
	class TimeManager : public Singleton<TimeManager>
	{
	private:
		UINT32 FPS;
		float elapseTime;
		ULONGLONG currTime, lastTime, elapsed;
		float m_fGametime;
		TimeManager() : FPS(0), elapseTime(0.0f), currTime(0), lastTime(0) {}
	public:
		VOID Initialize(UINT FPS);
		BOOL Update();
		FLOAT DeltaTime() CONST { return elapseTime; }	//소요된 시간 반환
		int GetGameTime() { return m_fGametime * 0.001f; }
		void SetGameTime(float time) {m_fGametime = time;}

		friend Singleton;
	};
#define TimeMgr TimeManager::GetInstance()
}

