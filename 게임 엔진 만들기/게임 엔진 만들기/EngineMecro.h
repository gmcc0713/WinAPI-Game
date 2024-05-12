//#pragma once
#pragma comment(lib,"msimg32.lib")
#include <crtdbg.h>
#include <Windows.h>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include "Component.h"

#ifndef ENGINE_MECRO_H	//#pragma once 실행 안될때 사용,전처리기에 해당 메크로 함수 없을때 #endif까지 실행
#define ENGINE_MECRO_H	// 두번째부터는 ENGINE_MECRO_H 셍성되있음

#ifndef DEL
#define DEL(a) if(a){delete a; a = nullptr;} //delete 메크로 함수
#endif //!DEL
#ifndef REL_DEL
#define REL_DEL(a) if(a){a->Release(); delete a; a = nullptr;}//Realease()
#endif //!REL_DEL

typedef std::function<VOID()> EventListener;
namespace ENGINE
{
	enum	//무명(no name) enum, 게임엔진에 사용되는 여러 기본 데이터 설정값
	{
		ClientSize_Width = 800,
		ClientSize_Height = 600,
		Client_Per_X = 50,
		Client_Per_Y = 50,	//0~100%
		FPS = 120		// 초당 프레임
	};
	__interface Scene
	{
		void Initialize();
		void Release();
		void Update(const float& deltaTime);
		void Draw();
	};
	
}
#endif	//!ENGINE_MECRO_H