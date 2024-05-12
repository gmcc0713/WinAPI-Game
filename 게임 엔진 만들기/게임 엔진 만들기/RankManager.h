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
		void SavePlayerRank();		//�÷��̾� ���Ͽ� ����
		void LoadPlayer();						//�÷��̾� ���Ͽ��� �ҷ�����
		void SortPlayer();						//�÷��̾� ����
		~RankManager();
		friend Singleton;
	};
	#define RankMgr RankManager::GetInstance()

}
