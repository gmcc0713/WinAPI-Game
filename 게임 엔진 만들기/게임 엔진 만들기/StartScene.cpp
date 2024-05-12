#include "StartScene.h"
void StartScene::Initialize()
{
	ResourceMgr->Load("background.bmp");
	ResourceMgr->Load("GameTitle.bmp");
	ResourceMgr->Load("base_panel.bmp");
	ResourceMgr->Load("StartBG.bmp");
	ResourceMgr->Load("background.bmp");
	ResourceMgr->Load("Start_Normal.bmp");
	ResourceMgr->Load("Start_Pressed.bmp");
	ResourceMgr->Load("Rank_Normal.bmp");
	ResourceMgr->Load("Rank_Pressed.bmp");
	ResourceMgr->Load("Quit_Normal.bmp");
	ResourceMgr->Load("Quit_Pressed.bmp");
	ResourceMgr->Load("Help_Normal.bmp");
	ResourceMgr->Load("Help_Pressed.bmp");

	m_background = ResourceMgr->GetBitmap("background.bmp");
	m_background->SetDrawSize(SceneMgr->GetWidth(), SceneMgr->GetHeight());
	
	m_StartSceneWindow = UIMgr->AddUI<UIImage>("StartSceneWindow Canvas");
	if (m_StartSceneWindow)
	{

		m_StartSceneWindow->Initialize("StartBG.bmp", DrawType::Transparent);
		m_StartSceneWindow->SetPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);


		UIImage* gameTitle = UIMgr->AddUI<UIImage>("Title Image", m_StartSceneWindow);
		gameTitle->Initialize("GameTitle.bmp", DrawType::Transparent);
		gameTitle->SetLocalPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight()*0.2f,true);

		UIButton* startBtn = UIMgr->AddUI<UIButton>("Start Btn", m_StartSceneWindow);
		startBtn->Initialize("Start_Normal.bmp", "Start_Pressed.bmp", "", "", DrawType::Transparent);
		startBtn->SetLocalPosition(m_StartSceneWindow->GetSize().cx * 0.5f, m_StartSceneWindow->GetSize().cy * 0.4f , true);
		startBtn->SetListener(std::bind(&StartScene::StartBtnHandler, this));

		UIButton* RankBtn = UIMgr->AddUI<UIButton>("Rank Btn", m_StartSceneWindow);
		RankBtn->Initialize("Rank_Normal.bmp", "Rank_Pressed.bmp", "", "", DrawType::Transparent);
		RankBtn->SetLocalPosition(m_StartSceneWindow->GetSize().cx * 0.5f, m_StartSceneWindow->GetSize().cy * 0.6f, true);
		RankBtn->SetListener(std::bind(&StartScene::RankBtnHandler, this));

		UIButton* quitBtn = UIMgr->AddUI<UIButton>("Quit Btn", m_StartSceneWindow);
		quitBtn->Initialize("Quit_Normal.bmp", "Quit_Pressed.bmp", "", "", DrawType::Transparent);
		quitBtn->SetLocalPosition(m_StartSceneWindow->GetSize().cx * 0.5f, m_StartSceneWindow->GetSize().cy * 0.8f , true);
		quitBtn->SetListener(std::bind(&StartScene::QuitBtnHandler, this));

		UIButton* HelpBtn = UIMgr->AddUI<UIButton>("Help Btn", m_StartSceneWindow);
		HelpBtn->Initialize("Help_Normal.bmp", "Help_Pressed.bmp", "", "", DrawType::Transparent);
		HelpBtn->SetLocalPosition(m_StartSceneWindow->GetSize().cx * 0.9f, m_StartSceneWindow->GetSize().cy * 0.8f, true);
		HelpBtn->SetListener(std::bind(&StartScene::HelpBtnHandler, this));
	}
}
void StartScene::Release()
{

}
void StartScene::Update(const float& deltaTime)
{
	m_StartSceneWindow->Update();

}
void StartScene::Draw()
{
	m_background->StretchBlt(0, 0);

	m_StartSceneWindow->Draw();

}
void StartScene::StartBtnHandler()
{

	TimeMgr->SetGameTime(0);
	ENGINE::SceneMgr->LoadScene("StageScene");

}
void StartScene::RankBtnHandler()
{

	ENGINE::SceneMgr->LoadScene("RankScene");

}
void StartScene::HelpBtnHandler()
{

	ENGINE::SceneMgr->LoadScene("HelpScene");
}
void StartScene::QuitBtnHandler()
{

	PostQuitMessage(0);
}