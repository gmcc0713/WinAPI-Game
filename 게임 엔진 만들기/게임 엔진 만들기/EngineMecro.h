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

#ifndef ENGINE_MECRO_H	//#pragma once ���� �ȵɶ� ���,��ó���⿡ �ش� ��ũ�� �Լ� ������ #endif���� ����
#define ENGINE_MECRO_H	// �ι�°���ʹ� ENGINE_MECRO_H �ļ�������

#ifndef DEL
#define DEL(a) if(a){delete a; a = nullptr;} //delete ��ũ�� �Լ�
#endif //!DEL
#ifndef REL_DEL
#define REL_DEL(a) if(a){a->Release(); delete a; a = nullptr;}//Realease()
#endif //!REL_DEL

typedef std::function<VOID()> EventListener;
namespace ENGINE
{
	enum	//����(no name) enum, ���ӿ����� ���Ǵ� ���� �⺻ ������ ������
	{
		ClientSize_Width = 800,
		ClientSize_Height = 600,
		Client_Per_X = 50,
		Client_Per_Y = 50,	//0~100%
		FPS = 120		// �ʴ� ������
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