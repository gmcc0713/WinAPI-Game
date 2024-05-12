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
		UIPanel* GetUI(std::string name);	//해당 이름의 ui가 map_UI에 있는지 확인, 있으면 해당UI 없으면 nullptr반환
		bool Remove(std::string name);		//해당 이름의 ui 삭제

		friend Singleton;
	};

	template<typename T>
	inline T* UIManager::AddUI(std::string name, UIPanel* parent)
	{
		if (name.empty()) return nullptr;

		auto iter = map_UI.find(name);	//map_UI에 name이 있는지 find 없으면 end return
		if (map_UI.end() != iter) return nullptr;	//map_UI에 있으면 nullptr return

		T* ui = new T;		//map_UI에 없으면 child에 추가후 ui return
		if (parent) parent->AddChildUI(ui);

		return ui;
	}
	#define UIMgr UIManager::GetInstance()
}
#endif // !UI_MANAGER_H

