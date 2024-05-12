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

		//map���� �� ���� Ž���� ���� �ڷᱸ��, �ߺ������� ��� X
		//map���� �� ���� �����͸� �����Ҷ� ���� ������ �����Ѵ�.
		std::unordered_map<UINT, InputState>keys;	//key �Է»��� ����
		std::map<UINT, InputState> mouse;		//���콺��ư���� ����.
		POINT mousePosition;	//���� ���콺 Ŀ���� ��ġ.
		std::string str;		//�Էµ� Ű�� ��������


		InputManager() : mousePosition({ 0,0 }) {}
	public:
		~InputManager();
		VOID Initialize() {}
		VOID Release();
		VOID Update();
		VOID InputProc(UINT message, WPARAM wParam, LPARAM lParam); //Input Procedure
		LPCSTR GetChar() { return str.c_str(); }	//�Է��� Ű�� ���������� �˾ƿ´�.
		BOOL GetKeyDown(UINT keyID) { return KeyCheck(keyID,InputState::DOWN); }	//Ȯ���Ϸ��� Ű�� ���� �����ӿ��� �������°�
		BOOL GetKeyPressed(UINT keyID) { return (KeyCheck(keyID, InputState::PRESSED) || KeyCheck(keyID, InputState::DOWN));}	//Ȯ���Ϸ��� Ű�� ������ �����ΰ�?
		BOOL GetKeyUp(UINT keyID) { return KeyCheck(keyID, InputState::UP); }//Ȯ���Ϸ��� Ű�� ���������ӿ��� �������� �ʾҴ°�?
		BOOL PressedAnyKey();
		BOOL GetMouseButtonDown(UINT keyID) { return ButtonCheck(keyID, InputState::DOWN);}
		BOOL GetMouseButtonPressed(UINT keyID) { return (ButtonCheck(keyID, InputState::PRESSED)||ButtonCheck(keyID,InputState::DOWN));}
		BOOL GetMouseButtonUp(UINT keyID) { return ButtonCheck(keyID, InputState::UP); }
		POINT GetMousePosition()CONST { return mousePosition; }

		LPCSTR GetKeyPressIsEnglish();
	private:
		VOID StartCapture();		//���콺 ������ �̵�����
		VOID EndCapture();			//���콺 ������ �̵����� ����
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