#include "InputManager.h"
#include "SceneManager.h"

namespace ENGINE
{
	InputManager::~InputManager() { Release(); }

	VOID InputManager::Release()
	{
		str = "";	//입력된 키 초기화
		keys.clear();	//키상태 초기화
		mouse.clear();	//마우스상태 초기화
		EndCapture();	//이동범위제한 해제
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
			case XBUTTON1: SetMouseButtonDown(VK_XBUTTON1); break; //마우스 왼쪽 뒤 버튼
			case XBUTTON2: SetMouseButtonDown(VK_XBUTTON2); break;	//마우스 왼쪽 앞 버튼
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
			case XBUTTON1: SetMouseButtonUp(VK_XBUTTON1); break; //마우스 왼쪽 뒤 버튼
			case XBUTTON2: SetMouseButtonUp(VK_XBUTTON2); break;	//마우스 왼쪽 앞 버튼
			}
		}
		break;
		case WM_MOUSEMOVE: SetMousePosition(lParam); break;
		}
	}
	BOOL InputManager::PressedAnyKey()	//키가 눌려져 있거나 현재프레임에 눌려져 있는가?
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

	VOID InputManager::StartCapture()//마우스 영역밖 이동제한
	{
		HWND hWnd = SceneMgr->GetHWND();
		SetCapture(hWnd);			//마우스가  영역밖에서도 값을 받아올수있음
		POINT leftTop = { 0,0 };
		POINT rightBottom = { SceneMgr->GetWidth() + 1,SceneMgr->GetHeight() + 1 };	

		ClientToScreen(hWnd, &leftTop);	//윈도우 화면상 기준이 된 좌표를 클라이언트 상으로 바꿈
		ClientToScreen(hWnd, &rightBottom);

		RECT clip = { leftTop.x,leftTop.y,rightBottom.x,rightBottom.y };
		ClipCursor(&clip);		//커서를 해당 위치에 고정
	}

	VOID InputManager::EndCapture()	//마우스 영역밖 이동제한 종료
	{
		ClipCursor(NULL);		//커서고정 해제
		ReleaseCapture();		//SetCapture후 해제
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
		if (keys.end() != iter) return (state == iter->second);	//해당 keyID가 keys에 있을때 그 키상태 반환

		keys.insert(std::make_pair(keyID, InputState::NONE));//해당 key 삽입

		return FALSE;
	}
	BOOL InputManager::ButtonCheck(UINT keyID, const InputState& state)
	{
		std::map<UINT, InputState>::iterator iter = mouse.find(keyID);
		if (mouse.end() != iter) return (state == iter->second);//현재 누른 key사 keys에 있을때 그 키상태 반환

		mouse.insert(std::make_pair(keyID, InputState::NONE));	//없으면 해당 key 삽입

		return FALSE;
	}

}		//namespace ENGINE