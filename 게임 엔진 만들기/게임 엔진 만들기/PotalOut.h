#pragma once
#include "EngineMecro.h"
#include"Components/SpriteRenderer.h"
#include"Components/SpriteAnimation.h"
#include "ResourceManager.h"


using namespace ENGINE;

class PotalOut : public GameObject
{
	enum class DATA { SPRITE_X = 3, SPRITE_Y = 1 };
private:

	SpriteRenderer* m_renderer;
	SpriteAnimation* m_animation;

public:
	PotalOut();
	void Initialize(float x, float y);
	void Update();
	void Draw();

};

