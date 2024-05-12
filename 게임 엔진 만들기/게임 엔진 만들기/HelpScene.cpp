#include "HelpScene.h"
void HelpScene::Initialize()
{
	ResourceMgr->Load("background.bmp");
	ResourceMgr->Load("TransparentBG.bmp");
	ResourceMgr->Load("Next_Normal.bmp");
	ResourceMgr->Load("Next_Pressed.bmp");
	ResourceMgr->Load("Back_Normal.bmp");
	ResourceMgr->Load("Back_Pressed.bmp");
	ResourceMgr->Load("Cancle_Normal.bmp");
	ResourceMgr->Load("Cancle_Pressed.bmp");
	for (int i = 0; i < (int)DATA::PAGE_COUNT; i++)
	{
		ResourceMgr->Load("HelpBG_" + std::to_string(i + 1)+".bmp");
	}

	m_background = ResourceMgr->GetBitmap("background.bmp");
	m_background->SetDrawSize(SceneMgr->GetWidth(), SceneMgr->GetHeight());

	m_HelpSceneWindow = UIMgr->AddUI<UIImage>("HelpSceneWindow Canvas");
	if (m_HelpSceneWindow)
	{
		m_HelpSceneWindow->Initialize("TransparentBG.bmp", DrawType::Transparent);
		m_HelpSceneWindow->SetPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight() * 0.5f, true);

		UIButton* nextBtn = UIMgr->AddUI<UIButton>("Next Btn", m_HelpSceneWindow);
		nextBtn->Initialize("Next_Normal.bmp", "Next_Pressed.bmp", "", "", DrawType::Transparent);
		nextBtn->SetLocalPosition(m_HelpSceneWindow->GetSize().cx*0.9f, m_HelpSceneWindow->GetSize().cy*0.85f , true);
		nextBtn->SetListener(std::bind(&HelpScene::NextBtnHandler, this));

		UIButton* backBtn = UIMgr->AddUI<UIButton>("Back Btn", m_HelpSceneWindow);
		backBtn->Initialize("Back_Normal.bmp", "Back_Pressed.bmp", "", "", DrawType::Transparent);
		backBtn->SetLocalPosition(m_HelpSceneWindow->GetSize().cx * 0.1f, m_HelpSceneWindow->GetSize().cy * 0.85f, true);
		backBtn->SetListener(std::bind(&HelpScene::BackBtnHandler, this));

		UIButton* CancleBtn = UIMgr->AddUI<UIButton>("Cancle Btn", m_HelpSceneWindow);
		CancleBtn->Initialize("Cancle_Normal.bmp", "Cancle_Pressed.bmp", "", "", DrawType::Transparent);
		CancleBtn->SetLocalPosition(m_HelpSceneWindow->GetSize().cx * 0.9f, m_HelpSceneWindow->GetSize().cy * 0.15f, true);
		CancleBtn->SetListener(std::bind(&HelpScene::QuitBtnHandler, this));

	}
	for (int i = 0; i < (int)DATA::PAGE_COUNT; i++)
	{
		m_HelpBG[i] = UIMgr->AddUI<UIImage>("HelpBG" + std::to_string(i+1));
		m_HelpBG[i]->Initialize("HelpBG_"+std::to_string(i+1)+".bmp", DrawType::Transparent);
		m_HelpBG[i]->SetPosition(SceneMgr->GetWidth() * 0.5f, SceneMgr->GetHeight() * 0.5f, true);
	}

	m_iPage = 0;
}
void HelpScene::Release()
{

}
void HelpScene::Update(const float& deltaTime)
{
	m_HelpBG[m_iPage]->Update();
	m_HelpSceneWindow->Update();
}
void HelpScene::Draw()
{
	m_background->StretchBlt(0, 0);

	m_HelpBG[m_iPage]->Draw();
	m_HelpSceneWindow->Draw();

}
void HelpScene::BackBtnHandler()
{
	if (m_iPage>0)
	{
		m_iPage--;
	}
}
void HelpScene::NextBtnHandler()
{
	if (m_iPage<(int)DATA::PAGE_COUNT-1)
	{
		m_iPage++;
	}
}
void HelpScene::QuitBtnHandler()
{
	ENGINE::SceneMgr->LoadScene("StartScene");
}