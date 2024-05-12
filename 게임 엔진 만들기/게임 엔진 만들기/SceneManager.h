#pragma once
#include "Singleton.h"

#ifndef  SCENE_MANAGER_H
#define  SCENE_MANAGER_H


namespace ENGINE
{
	class SceneManager : public Singleton<SceneManager>
	{
	private:
		HWND hWnd;
		HDC hDC, hBackDC;
		UINT32 width, height;
		HFONT m_font;

		Scene* currScene;
		std::string nextScene;
		std::map<std::string, Scene*> scenes;

		SceneManager() : hWnd(NULL), hDC(NULL), hBackDC(NULL), width(0), height(0), currScene(NULL) {}
	public:
		~SceneManager();
		VOID Initialize(HWND hWnd, UINT32 width, UINT32 height);
		VOID Release();
		VOID Render();

		bool RegisterScene(LPCSTR sceneName, Scene* scene);	//Scene등록
		bool LoadScene(LPCSTR sceneName);	//불러올 Scene을 설정
		
		HFONT GetFont()CONST { return m_font; }
		UINT32 GetWidth() CONST { return width; }		//윈도우 클라이언트 너비
		UINT32 GetHeight() CONST { return height; }		//윈도우 클라이언트 높이
		HWND GetHWND() CONST { return hWnd; }
		HDC GetBackDC() CONST { return hBackDC; }

	private:
		VOID SetScene();	//등록된 SCENE적용
		VOID Update();
		VOID Draw();
		HBITMAP CreateDIBSectionRe();	//Back Bitmap을 만들기 위한 비트맵 Creater
	
		friend Singleton;
	};//class SceneManager
#define SceneMgr SceneManager::GetInstance()
}
#endif // ! SCENE_MANAGER_H
