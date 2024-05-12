#include "InputManager.h"
#include "SceneManager.h"

namespace ENGINE
{
	InputManager::~InputManager() { Release(); }

	VOID InputManager::Release()
	{
		str = "";	//�Էµ� Ű �ʱ�ȭ
		keys.clear();	//Ű���� �ʱ�ȭ
		mouse.clear();	//���콺���� �ʱ�ȭ
		EndCapture();	//�̵��������� ����
	}

	VOID InputManager::Update()
	{
		str = "";
		for (std::pair<CONST UINT, InputState>& key : keys)
		{
			switch (key.second)
			{
			case InputState::DOWN: key.second = InputState::PRESSED; break;
			case InputState::UP: key.second = InputState::NONE; break;
			}
		}
		for (std::pair<CONST UINT, InputState>& button : mouse)
		{
			switch (button.second)
			{
			case InputState::DOWN: button.second = InputState::PRESSED; break;
			case InputState::UP: button.second = InputState::NONE; break;
			}
		}
	}

	VOID InputManager::InputProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CHAR: str = wParam; break;
		case WM_KEYDOWN: case WM_SYSKEYDOWN: SetKeyDown(wParam); break;
		case WM_KEYUP: case WM_SYSKEYUP: SetKeyUp(wParam); break;
		case WM_LBUTTONDOWN: SetMouseButtonDown(VK_LBUTTON); break;
		case WM_RBUTTONDOWN: SetMouseButtonDown(VK_RBUTTON); break;
		case WM_MBUTTONDOWN: SetMouseButtonDown(VK_MBUTTON); break;
		case WM_XBUTTONDOWN:
		{
			switch (wParam)
			{
			case XBUTTON1: SetMouseButtonDown(VK_XBUTTON1); break; //���콺 ���� �� ��ư
			case XBUTTON2: SetMouseButtonDown(VK_XBUTTON2); break;	//���콺 ���� �� ��ư
			}
		}
		break;
		case WM_LBUTTONUP: SetMouseButtonUp(VK_LBUTTON); break;
		case WM_RBUTTONUP: SetMouseButtonUp(VK_RBUTTON); break;
		case WM_MBUTTONUP: SetMouseButtonUp(VK_MBUTTON); break;
		case WM_XBUTTONUP:
		{
			switch (wParam)
			{
			case XBUTTON1: SetMouseButtonUp(VK_XBUTTON1); break; //���콺 ���� �� ��ư
			case XBUTTON2: SetMouseButtonUp(VK_XBUTTON2); break;	//���콺 ���� �� ��ư
			}
		}
		break;
		case WM_MOUSEMOVE: SetMousePosition(lParam); break;
		}
	}
	BOOL InputManager::PressedAnyKey()	//Ű�� ������ �ְų� ���������ӿ� ������ �ִ°�?
	{
		for (std::pair<CONST UINT, InputState>& key : keys) 
		{
			switch (key.second)
			{
			case InputState::DOWN:
			case InputState::PRESSED:
				return TRUE;
			}
		}
		return false;
	}

	LPCSTR InputManager::GetKeyPressIsEnglish()
	{
		if(str >= "A" && str <= "Z")
			return str.c_str();
	}

	VOID InputManager::StartCapture()//���콺 ������ �̵�����
	{
		HWND hWnd = SceneMgr->GetHWND();
		SetCapture(hWnd);			//���콺��  �����ۿ����� ���� �޾ƿü�����
		POINT leftTop = { 0,0 };
		POINT rightBottom = { SceneMgr->GetWidth() + 1,SceneMgr->GetHeight() + 1 };	

		ClientToScreen(hWnd, &leftTop);	//������ ȭ��� ������ �� ��ǥ�� Ŭ���̾�Ʈ ������ �ٲ�
		ClientToScreen(hWnd, &rightBottom);

		RECT clip = { leftTop.x,leftTop.y,rightBottom.x,rightBottom.y };
		ClipCursor(&clip);		//Ŀ���� �ش� ��ġ�� ����
	}

	VOID InputManager::EndCapture()	//���콺 ������ �̵����� ����
	{
		ClipCursor(NULL);		//Ŀ������ ����
		ReleaseCapture();		//SetCapture�� ����
	}
	VOID InputManager::SetMouseButtonDown(UINT keyID)
	{
		StartCapture();
		mouse[keyID] = InputState::DOWN;
	}
	VOID InputManager::SetMouseButtonUp(UINT keyID)
	{
		mouse[keyID] = InputState::UP;
		EndCapture();
	}
	BOOL InputManager::KeyCheck(UINT keyID, CONST InputManager::InputState& state)
	{
		std::unordered_map<UINT, InputState>::iterator iter = keys.find(keyID);
		if (keys.end() != iter) return (state == iter->second);	//�ش� keyID�� keys�� ������ �� Ű���� ��ȯ

		keys.insert(std::make_pair(keyID, InputState::NONE));//�ش� key ����

		return FALSE;
	}
	BOOL InputManager::ButtonCheck(UINT keyID, const InputState& state)
	{
		std::map<UINT, InputState>::iterator iter = mouse.find(keyID);
		if (mouse.end() != iter) return (state == iter->second);//���� ���� key�� keys�� ������ �� Ű���� ��ȯ

		mouse.insert(std::make_pair(keyID, InputState::NONE));	//������ �ش� key ����

		return FALSE;
	}

}		//namespace ENGINE