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

		void Initialize();	//초기화
		Bitmap* GetBitmap(const std::string& name);
		bool Load(const std::string& fileName);//비트맵이미지 로드
		//폴더의 모든 비트맵 이미지를 로드. 하위폴더는 검색하지 않는다
		void LoadAll(const std::string& directoryName = "");
		//로드되어있는 모든 리소스 삭제
		void Clear();

		friend Singleton;
	};
#define ResourceMgr ResourceManager::GetInstance()

}
#endif // !RESOURCE_MANAGER_H
