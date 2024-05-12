#include "RankManager.h"
namespace ENGINE
{

	bool compare(const PlayerInfo& player1, const PlayerInfo& player2);
	bool compare(const PlayerInfo& player1, const PlayerInfo& player2)
	{
		if (player1.time < player2.time)
			return  true;
		else if (player1.life < player2.life)
			return false;
		else
			return false;
	}

	void RankManager::Initialize()
	{
		LoadPlayer();
	}
	void RankManager::SortPlayer() //Á¤·Ä
	{
		std::sort(m_vecPlayer.begin(), m_vecPlayer.end(), compare);
	}
	void RankManager::SavePlayerRank()
	{
		std::ofstream save;
		save.open("Rank.txt");
		for (PlayerInfo player : m_vecPlayer)
		{
			save << std::endl << player.name << " ";
			save << player.time << " ";
			save << player.life;
		}
		save.close();
	}
	void RankManager::LoadPlayer()   
	{
		std::ifstream load;
		m_vecPlayer.clear();
		load.open("Rank.txt");
		if (load.is_open())
		{
			while (!load.eof())
			{
				PlayerInfo player;
				load >> player.name;
				if (player.name == "") break;
				load >> player.time;
				load >> player.life;
				m_vecPlayer.push_back(player);
			}
			load.close();
		}
	}
	void RankManager::RegistePlayerNewRank(PlayerInfo player)
	{
		m_vecPlayer.push_back(player);

		SortPlayer();
		if (m_vecPlayer.size() > 5)
		{
			m_vecPlayer.pop_back();
		}

		SavePlayerRank();
	}
	RankManager::~RankManager()
	{
	}
}                                                                                                                                                                                                                                        