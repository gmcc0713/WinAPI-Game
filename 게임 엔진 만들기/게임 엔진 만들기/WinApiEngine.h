#pragma once
#include "EngineMecro.h"
#include "SceneManager.h"
#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H
namespace ENGINE
{
	class WinApiEngine
	{
	private:
		BOOL isInit;
		INT32 x, y;
		UINT32 width, height;
		std::wstring title;

		WinApiEngine();
	public:
		WinApiEngine(HINSTANCE hInstance, std::wstring titile, INT32 per_x,
			INT32 per_y, UINT32 width, UINT32 height);
		~WinApiEngine();

		INT Run();
		VOID Release();
	};
}

#endif //!ENGINE_MAIN_H