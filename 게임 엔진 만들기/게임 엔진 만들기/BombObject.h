#pragma once
#include "EngineMecro.h"
#include "Item.h"
#include "BombEffect.h"
#include "TimeManager.h"
class Player;
class BombObject : public Item
{
	enum class Data { SpritesX = 2, SpritesY = 1 };
private:
	
	float m_fTimer;
	float m_fFrameRate;
	BombEffect m_BombEffect;
	SpriteAnimation* m_animation;
public:
	BombObject();
	
	void Initialize(float x, float y);
	void Draw();
	virtual bool Update(const float& deltaTime);
	bool EffectCollideCheck(Player* player);
};

