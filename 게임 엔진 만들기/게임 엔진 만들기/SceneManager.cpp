#include "SceneManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "RankManager.h"
#include"ResourceManager.h"
#include "UIManager.h"
namespace ENGINE
{
	SceneManager::~SceneManager() { Release(); }

	VOID SceneManager::Initialize(HWND hWnd, UINT32 width, UINT height)
	{
		if (!hWnd) return;

		this->hWnd = hWnd;
		this->width = width;
		this->height = height;

		hDC = GetDC(hWnd);
		hBackDC = CreateCompatibleDC(hDC);
		m_font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("DungGeunMo"));

		TimeMgr->Initialize(FPS);	//FPS : EngineMecro::ENGINE::enum::FPS
		InputMgr->Initialize();		//InputManager �ʱ�ȭ
		ResourceMgr->Initialize();
		UIMgr->Initialize();
	}
	VOID SceneManager::Release()
	{
		currScene = NULL;
		UIMgr->Destroy();
		ResourceMgr->Destroy();
		InputMgr->Destroy();
		TimeMgr->Destroy();
		RankMgr->Destroy();

		for (std::pair<std::string, Scene*>scene : scenes) REL_DEL(scene.second);			//make_pair�� �ٸ��� Ÿ���� ����������Ѵ�.

		scenes.clear();

		DeleteObject(hBackDC);
		DeleteObject(m_font);
		ReleaseDC(hWnd, hDC);
	}
	VOID SceneManager::Render()
	{

		if (!TimeMgr->Update()) return;	

		if (currScene)	//������� ������� ������
		{
			Update();
			Draw();
			
			InputMgr->Update();
		}
		SetScene();
	}

	VOID SceneManager::SetScene()
	{
		if (nextScene.empty()) return;	//�������� ������

		if (currScene)		
		{
			currScene->Release(); //����� ����
			UIMgr->Clear();
			ResourceMgr->Clear();
		}
		currScene = scenes[nextScene]; //������ ���� ���� �ֱ�
		currScene->Initialize();		//���� �� �ʱ�ȭ
		nextScene = "";					//���� �� ����
	}

	VOID SceneManager::Update()
	{
		UIMgr->Update();
		currScene->Update(TimeMgr->DeltaTime());
	}

	VOID SceneManager::Draw()
	{
		HBITMAP backBitmap = CreateDIBSectionRe();
		SelectObject(hBackDC, backBitmap);

		currScene->Draw();				//����� �׸���
		UIMgr->Draw();

		BitBlt(hDC, 0, 0, width, height, hBackDC, 0, 0, SRCCOPY);		//backDC���� �Űܱ׸���
		DeleteObject(backBitmap);
	}

	bool SceneManager::RegisterScene(LPCSTR sceneName, Scene* scene)
	{
		if ("" == sceneName || !scene || scenes.find(sceneName) != scenes.end())
		{
			return false;
		}
		scenes.insert(std::make_pair(sceneName, scene));		
		return false;
	}
	bool SceneManager::LoadScene(LPCSTR sceneName)
	{
		auto scene = scenes.find(sceneName);
		if ("" == sceneName || scene == scenes.end())
		{
			return false;
		}
		nextScene = sceneName;
		return true;
	}

	HBITMAP SceneManager::CreateDIBSectionRe()
	{
		BITMAPINFO bmpInfo;
		ZeroMemory(&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER));
		bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfo.bmiHeader.biBitCount = 32;
		bmpInfo.bmiHeader.biWidth = width;
		bmpInfo.bmiHeader.biHeight = height;
		bmpInfo.bmiHeader.biPlanes = 1;
		LPVOID pBits;
		return CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	}
}