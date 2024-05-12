#pragma once
#include "Singleton.h"
#include<unordered_map>
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

namespace ENGINE
{
	class InputManager : public Singleton<InputManager>
	{
	private:
		enum class InputState {NONE,DOWN,PRESSED,UP};

		//map보다 더 빠른 탐색을 위한 자료구조, 중복데이터 허용 X
		//map보다 더 많은 데이터를 관리할때 높은 성능을 발휘한다.
		std::unordered_map<UINT, InputState>keys;	//key 입력상태 정보
		std::map<UINT, InputState> mouse;		//마우스버튼상태 정보.
		POINT mousePosition;	//현재 마우스 커서의 위치.
		std::string str;		//입력된 키의 문자정보


		InputManager() : mousePosition({ 0,0 }) {}
	public:
		~InputManager();
		VOID Initialize() {}
		VOID Release();
		VOID Update();
		VOID InputProc(UINT message, WPARAM wParam, LPARAM lParam); //Input Procedure
		LPCSTR GetChar() { return str.c_str(); }	//입력한 키의 문자정보를 알아온다.
		BOOL GetKeyDown(UINT keyID) { return KeyCheck(keyID,InputState::DOWN); }	//확인하려는 키가 현재 프레임에서 눌러졌는가
		BOOL GetKeyPressed(UINT keyID) { return (KeyCheck(keyID, InputState::PRESSED) || KeyCheck(keyID, InputState::DOWN));}	//확인하려는 키가 눌러진 상태인가?
		BOOL GetKeyUp(UINT keyID) { return KeyCheck(keyID, InputState::UP); }//확인하려는 키가 현재프레임에서 눌러지지 않았는가?
		BOOL PressedAnyKey();
		BOOL GetMouseButtonDown(UINT keyID) { return ButtonCheck(keyID, InputState::DOWN);}
		BOOL GetMouseButtonPressed(UINT keyID) { return (ButtonCheck(keyID, InputState::PRESSED)||ButtonCheck(keyID,InputState::DOWN));}
		BOOL GetMouseButtonUp(UINT keyID) { return ButtonCheck(keyID, InputState::UP); }
		POINT GetMousePosition()CONST { return mousePosition; }

		LPCSTR GetKeyPressIsEnglish();
	private:
		VOID StartCapture();		//마우스 영역밖 이동제한
		VOID EndCapture();			//마우스 영역밖 이동제한 종료
		VOID SetKeyDown(UINT keyID) { keys[keyID] = InputState::DOWN; }
		VOID SetKeyUp(UINT keyID) { keys[keyID] = InputState::UP; }
		VOID SetMouseButtonDown(UINT keyID);
		VOID SetMouseButtonUp(UINT keyID);
		VOID SetMousePosition(LPARAM lParam) { mousePosition = { LOWORD(lParam),HIWORD(lParam) }; }

		BOOL KeyCheck(UINT keyID,CONST InputState& state);
		BOOL ButtonCheck(UINT keyID, CONST InputState& state);

		friend Singleton;
	};
#define InputMgr InputManager::GetInstance()
}

#endif //!INPUT_MANAGER_H