#pragma once
#include "EngineMecro.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
using namespace ENGINE;
class StartScene : public Scene
{
private:
	Bitmap* m_background = nullptr;
	UIImage* m_StartSceneWindow;
	float m_fTimer;

	void StartBtnHandler();
	void RankBtnHandler();
	void QuitBtnHandler();
	void HelpBtnHandler();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update(const float& deltaTime) override;
	virtual void Draw()override;
};

