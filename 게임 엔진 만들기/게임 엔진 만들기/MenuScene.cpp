#include "MenuScene.h"
void MenuScene::Initialize()
{
	ResourceMgr->Load("background.bmp");
	ResourceMgr->Load("Start_Normal.bmp");
	ResourceMgr->Load("Start_Pressed.bmp");
	ResourceMgr->Load("Rank_Normal.bmp");
	ResourceMgr->Load("Rank_Pressed.bmp");
	ResourceMgr->Load("Quit_Normal.bmp");
	ResourceMgr->Load("Quit_Pressed.bmp");

	m_background = ResourceMgr->GetBitmap("background.bmp");
	m_background->SetDrawSize(SceneMgr->GetWidth(), SceneMgr->GetHeight());

	m_MenuSceneWindow = UIMgr->AddUI<UIImage>("MenuSceneWindow Canvas");
	if (m_MenuSceneWindow)
	{

		m_MenuSceneWindow->Initialize("background.bmp", DrawType::Transparent);
		m_MenuSceneWindow->SetPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);

		UIButton* startBtn = UIMgr->AddUI<UIButton>("Start Btn", m_MenuSceneWindow);
		startBtn->Initialize("Start_Normal.bmp", "Start_Pressed.bmp", "", "", DrawType::Transparent);
		startBtn->SetLocalPosition(m_MenuSceneWindow->GetSize().cx * 0.5f, m_MenuSceneWindow->GetSize().cy * 0.5f-200, true);
		startBtn->SetListener(std::bind(&MenuScene::StartBtnHandler, this));

		UIButton* RankBtn = UIMgr->AddUI<UIButton>("Rank Btn", m_MenuSceneWindow);
		RankBtn->Initialize("Rank_Normal.bmp", "Rank_Pressed.bmp", "", "", DrawType::Transparent);
		RankBtn->SetLocalPosition(m_MenuSceneWindow->GetSize().cx * 0.5f, m_MenuSceneWindow->GetSize().cy * 0.5f, true);
		RankBtn->SetListener(std::bind(&MenuScene::RankBtnHandler, this));

		UIButton* quitBtn = UIMgr->AddUI<UIButton>("Quit Btn", m_MenuSceneWindow);
		quitBtn->Initialize("Quit_Normal.bmp", "Quit_Pressed.bmp", "", "", DrawType::Transparent);
		quitBtn->SetLocalPosition(m_MenuSceneWindow->GetSize().cx * 0.5f, m_MenuSceneWindow->GetSize().cy * 0.5f + 200,true);
		quitBtn->SetListener(std::bind(&MenuScene::QuitBtnHandler, this));

	}

}
void MenuScene::Release()
{

}
void MenuScene::Update(const float& deltaTime)
{
	m_MenuSceneWindow->Update();

}
void MenuScene::Draw()
{
	m_background->StretchBlt(0, 0);

	m_MenuSceneWindow->Draw();

}
void MenuScene::StartBtnHandler()
{
	TimeMgr->SetGameTime(0);
	ENGINE::SceneMgr->LoadScene("StageScene");
}
void MenuScene::RankBtnHandler()
{
	ENGINE::SceneMgr->LoadScene("RankScene");
}
void MenuScene::QuitBtnHandler()
{
	PostQuitMessage(0);
}