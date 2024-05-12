#pragma once
#include "Singleton.h"
#include "UIButton.h"
#include "UILabel.h"
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

namespace ENGINE
{
	class UIManager : public Singleton<UIManager>
	{
	private:
		std::map<std::string, UIPanel*>map_UI;
		std::vector<UIPanel*> child_UI;

		UIManager() {}
	public:
		~UIManager();

		void Initialize();
		void Clear();
		void Update();
		void Draw();
		template<typename T> T* AddUI(std::string name, UIPanel* parent = nullptr);
		UIPanel* GetUI(std::string name);	//�ش� �̸��� ui�� map_UI�� �ִ��� Ȯ��, ������ �ش�UI ������ nullptr��ȯ
		bool Remove(std::string name);		//�ش� �̸��� ui ����

		friend Singleton;
	};

	template<typename T>
	inline T* UIManager::AddUI(std::string name, UIPanel* parent)
	{
		if (name.empty()) return nullptr;

		auto iter = map_UI.find(name);	//map_UI�� name�� �ִ��� find ������ end return
		if (map_UI.end() != iter) return nullptr;	//map_UI�� ������ nullptr return

		T* ui = new T;		//map_UI�� ������ child�� �߰��� ui return
		if (parent) parent->AddChildUI(ui);

		return ui;
	}
	#define UIMgr UIManager::GetInstance()
}
#endif // !UI_MANAGER_H

