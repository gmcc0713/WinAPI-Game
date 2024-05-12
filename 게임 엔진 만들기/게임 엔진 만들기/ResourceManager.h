#pragma once
#include "Singleton.h"
#include "Bitmap.h"
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
namespace ENGINE
{
	static const char* defaultPath = "Resources\\";
	class ResourceManager : public Singleton<ResourceManager>
	{
	private:
		std::map<std::string, Bitmap*> resources;

		ResourceManager() {}
	public:
		~ResourceManager();

		void Initialize();	//�ʱ�ȭ
		Bitmap* GetBitmap(const std::string& name);
		bool Load(const std::string& fileName);//��Ʈ���̹��� �ε�
		//������ ��� ��Ʈ�� �̹����� �ε�. ���������� �˻����� �ʴ´�
		void LoadAll(const std::string& directoryName = "");
		//�ε�Ǿ��ִ� ��� ���ҽ� ����
		void Clear();

		friend Singleton;
	};
#define ResourceMgr ResourceManager::GetInstance()

}
#endif // !RESOURCE_MANAGER_H
