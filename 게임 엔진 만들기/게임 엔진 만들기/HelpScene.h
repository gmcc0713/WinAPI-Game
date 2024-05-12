#pragma once
#include "EngineMecro.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
using namespace ENGINE;
class HelpScene : public Scene
{
	enum class DATA{ PAGE_COUNT = 3};
private:
	Bitmap* m_background = nullptr;
	UIImage* m_HelpSceneWindow;
	UIImage* m_HelpBG[(int)DATA::PAGE_COUNT];
	int m_iPage;
	float m_fTimer;

	void NextBtnHandler();
	void BackBtnHandler();
	void QuitBtnHandler();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update(const float& deltaTime) override;
	virtual void Draw()override;
};

