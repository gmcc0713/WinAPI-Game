#include "RankScene.h"
void RankScene::Initialize()
{
	ResourceMgr->Load("background.bmp");
	ResourceMgr->Load("RankBG.bmp");

	RankMgr->LoadPlayer();
	m_vecPlayer = RankMgr->GetRankPlayer();

	m_background = ResourceMgr->GetBitmap("background.bmp");
	m_background->SetDrawSize(SceneMgr->GetWidth(), SceneMgr->GetHeight());

	m_RankSceneWindow = UIMgr->AddUI<UIButton>("RankScene Canvas");
	if (m_RankSceneWindow)
	{
		m_RankSceneWindow->Initialize("RankBG.bmp", "RankBG.bmp","","", DrawType::Transparent);
		m_RankSceneWindow->SetPosition(0, 0);
		m_RankSceneWindow->SetListener(std::bind(&RankScene::PressRankSceneHandler, this));
		for (int i =0;i<5;i++)
		{
			m_arrRankLabel[i] = UIMgr->AddUI<UILabel>("Stage Label" + std::to_string(i), m_RankSceneWindow);
			m_arrRankLabel[i]->Initialize(GetPlayerInfoToVector(i), RGB(255, 255, 255), SceneMgr->GetFont());
			m_arrRankLabel[i]->SetPosition(SceneMgr->GetWidth()*0.15f, SceneMgr->GetHeight() * 0.1f*(i+3));
		}
	}

}
void RankScene::PressRankSceneHandler()
{
	ENGINE::SceneMgr->LoadScene("StartScene");
}
void RankScene::Release()
{

}
void RankScene::Update(const float& deltaTime)
{
	SetNewRank();

	m_RankSceneWindow->Update();

}
void RankScene::Draw()
{
	m_background->StretchBlt(0, 0);

	
	m_RankSceneWindow->Draw();

}
void RankScene::SetNewRank()
{
	m_vecPlayer = RankMgr->GetRankPlayer();
	for (int i = 0; i < 5; i++)
	{
		m_arrRankLabel[i]->SetText(GetPlayerInfoToVector(i));
	}
}
std::string RankScene::GetPlayerInfoToVector(int index)
{
	if (index < m_vecPlayer.size())
	{
		return std::to_string(index + 1) + " 등  " + "이름 : " + m_vecPlayer[index].name + "   시간 : " + std::to_string(m_vecPlayer[index].time) + "   목숨 : " + std::to_string(m_vecPlayer[index].life);
	}
	return "";
}