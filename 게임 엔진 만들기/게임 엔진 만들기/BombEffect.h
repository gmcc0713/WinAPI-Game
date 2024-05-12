#pragma once
#include"EngineMecro.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "ResourceManager.h"
#include "TimeManager.h"
using namespace ENGINE;
class BombEffect : GameObject
{
enum class Data { SpritesX = 8, SpritesY = 1, Speed = 200, };

private:
	bool m_bEnable;
	float m_fTimer;
	float m_fFrameRate;
	SpriteRenderer* m_renderer;
	SpriteAnimation* m_animation;
public:
	BombEffect();
	RECT GetRect();
	bool GetEnable() { return m_bEnable; }
	void Start(float x,float y);
	bool Update(float deltaTime);
	void Draw();
	void Initialize(float x, float y);
};

