#include "UIManager.h"


namespace ENGINE
{
	UIManager::~UIManager() { Clear(); }
	void UIManager::Initialize() { Clear(); }

	void UIManager::Clear()
	{
		//map_UI�� ��ü �Ҵ� ������ ����
		for (std::pair<std::string, UIPanel*> pair : map_UI) DEL(pair.second);	
			map_UI.clear();
	}
	void UIManager::Update()
	{
		//�θ� ������� �θ��ʿ��� Update()�Լ��� ȣ���ϰ� �ִ�
		for (std::pair<std::string, UIPanel*> pair : map_UI)
		{
			if (!pair.second->GetParent()) pair.second->Update();//�θ�Update ���� �ڽĵ��� Update�Լ� ȣ��
		}
	}
	void UIManager::Draw()
	{
		//�θ� ������� �θ��� ���� Draw �Լ��� ȣ���ϰ� �ִ�.
		for(std::pair<std::string,UIPanel*> pair : map_UI)
			if(!pair.second->GetParent()) pair.second->Draw();	//�θ�Draw ���� �ڽĵ��� Draw�Լ� ȣ��
	}
	UIPanel* UIManager::GetUI(std::string name)
	{
		auto iter = map_UI.find(name);		
		if (map_UI.end() != iter) return iter->second;

		return nullptr;
	}
	bool UIManager::Remove(std::string name)
	{
		auto ui = GetUI(name);	//�ش� �̸��� ui ã�� ������ nullptr

		if (nullptr != ui)
		{
			map_UI.erase(name);
			DEL(ui);

			return true;
		}
		return false;
	}
}