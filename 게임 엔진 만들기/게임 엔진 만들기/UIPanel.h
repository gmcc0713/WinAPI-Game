#pragma once
#include "EngineMecro.h"
#ifndef UI_PANEL_H
#define UI_PANELl_H

namespace ENGINE
{
	enum class UIType {PANEL,IMAGE,BUTTON,LABEL};
	class UIPanel
	{
	protected:
		bool isEnable, pivotCenter;
		POINT position, localPosition;//화면상 위치, 부모와의 위치
		RECT rect;
		SIZE size;
		UIPanel* parent;
		std::vector<UIPanel*> child;
		UIType uiType;

	public:
		UIPanel();
		virtual ~UIPanel();

	private:
		void SetParent(UIPanel* parent) { this->parent = parent; }
		void SetLocalPos(int x, int y);
	protected:
		virtual void SetRect(bool pivotCenter) { rect = { localPosition.x,localPosition.y,localPosition.x,localPosition.y }; }
	public:
		virtual void SetPosition(int x, int y, bool pivotCenter = false); //월드(스크린) 좌표상의 위치.
		virtual void SetLocalPosition(int x, int y, bool pivotCenter = false); //부모 UI를 중심으로 한 위치
		virtual void Update();
		virtual void Draw();

		//자식으로 추가된 UI는 알아서 메모리를 해제한다
		UIPanel* AddChildUI(UIPanel* ui);//계층구조, 자식UI추가
		void RemoveChildUI(UIPanel* ui);// 자식에서 제외하고 메모리 해제를 하지 않는다
		void RefreshPos();	//변경된 자신의 위치를 중심으로 자식 UI위치를 재배치

		void SetEnable(bool enable) { isEnable = enable; }
		bool Enable() const { return child.size(); }

		unsigned int GetChildCount() const { return child.size(); }
		UIPanel* GetChild(int index);
		UIPanel* GetParent() const { return parent; }
		POINT GetPosition() const { return position; }
		POINT GetLocalPosition() const { return localPosition; }
		UIType GetUIType() const { return uiType; }
		SIZE GetSize() const { return size; }

	
	
	};
}
#endif // !UI_PANEL_H

