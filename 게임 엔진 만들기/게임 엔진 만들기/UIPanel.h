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
		POINT position, localPosition;//ȭ��� ��ġ, �θ���� ��ġ
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
		virtual void SetPosition(int x, int y, bool pivotCenter = false); //����(��ũ��) ��ǥ���� ��ġ.
		virtual void SetLocalPosition(int x, int y, bool pivotCenter = false); //�θ� UI�� �߽����� �� ��ġ
		virtual void Update();
		virtual void Draw();

		//�ڽ����� �߰��� UI�� �˾Ƽ� �޸𸮸� �����Ѵ�
		UIPanel* AddChildUI(UIPanel* ui);//��������, �ڽ�UI�߰�
		void RemoveChildUI(UIPanel* ui);// �ڽĿ��� �����ϰ� �޸� ������ ���� �ʴ´�
		void RefreshPos();	//����� �ڽ��� ��ġ�� �߽����� �ڽ� UI��ġ�� ���ġ

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

