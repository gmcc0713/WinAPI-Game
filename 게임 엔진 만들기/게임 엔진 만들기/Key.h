#pragma once
#include "EngineMecro.h"
#include "Item.h"
#include "BombEffect.h"
class Key : public Item
{
public:
	Key();
	void Initialize(float x, float y);
	void Draw();
	virtual bool Update(const float& deltaTime);					//key�� ���������� true 
	virtual bool EffectCollideCheck(Player* player);		
};

