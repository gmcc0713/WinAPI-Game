#pragma once

#include "EngineMecro.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "RankManager.h"
using namespace ENGINE;

class RankScene :public Scene
{
private:
	Bitmap* m_background = nullptr;
	UIButton* m_RankSceneWindow;
	UILabel* m_arrRankLabel[5];

	std::vector<PlayerInfo> m_vecPlayer;
public:

	void PressRankSceneHandler();
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update(const float& deltaTime) override;
	virtual void Draw()override;
	void SetNewRank();
	std::string GetPlayerInfoToVector(int index);
};


