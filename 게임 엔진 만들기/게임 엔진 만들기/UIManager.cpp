#include "UIManager.h"


namespace ENGINE
{
	UIManager::~UIManager() { Clear(); }
	void UIManager::Initialize() { Clear(); }

	void UIManager::Clear()
	{
		//map_UI속 객체 할당 해제후 삭제
		for (std::pair<std::string, UIPanel*> pair : map_UI) DEL(pair.second);	
			map_UI.clear();
	}
	void UIManager::Update()
	{
		//부모가 있을경우 부모쪽에서 Update()함수를 호출하고 있다
		for (std::pair<std::string, UIPanel*> pair : map_UI)
		{
			if (!pair.second->GetParent()) pair.second->Update();//부모Update 에서 자식들의 Update함수 호출
		}
	}
	void UIManager::Draw()
	{
		//부모가 있을경우 부모쪽 에서 Draw 함수를 호출하고 있다.
		for(std::pair<std::string,UIPanel*> pair : map_UI)
			if(!pair.second->GetParent()) pair.second->Draw();	//부모Draw 에서 자식들의 Draw함수 호출
	}
	UIPanel* UIManager::GetUI(std::string name)
	{
		auto iter = map_UI.find(name);		
		if (map_UI.end() != iter) return iter->second;

		return nullptr;
	}
	bool UIManager::Remove(std::string name)
	{
		auto ui = GetUI(name);	//해당 이름의 ui 찾기 없으면 nullptr

		if (nullptr != ui)
		{
			map_UI.erase(name);
			DEL(ui);

			return true;
		}
		return false;
	}
}