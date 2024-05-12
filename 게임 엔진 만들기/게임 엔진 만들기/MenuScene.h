#pragma once
#include "EngineMecro.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
using namespace ENGINE;
class MenuScene : public Scene
{
private:
	Bitmap* m_background = nullptr;
	UIImage* m_MenuSceneWindow;


	float m_fTimer;

	void StartBtnHandler();
	void RankBtnHandler();
	void QuitBtnHandler();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update(const float& deltaTime) override;
	virtual void Draw()override;
};
