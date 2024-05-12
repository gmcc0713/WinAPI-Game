#pragma once
#include "Singleton.h"
#include <algorithm>
#include <fstream>
namespace ENGINE
{
	struct PlayerInfo
	{
		std::string name;
		int life;
		int time;
	};
	class RankManager : public Singleton<RankManager>
	{
	private:
		std::vector<PlayerInfo> m_vecPlayer;
		RankManager() {};
	public:
		void Initialize();
		std::vector<PlayerInfo> GetRankPlayer() { return m_vecPlayer; }
		void RegistePlayerNewRank(PlayerInfo player);
		void SavePlayerRank();		//플레이어 파일에 저장
		void LoadPlayer();						//플레이어 파일에서 불러오기
		void SortPlayer();						//플레이어 정렬
		~RankManager();
		friend Singleton;
	};
	#define RankMgr RankManager::GetInstance()

}
