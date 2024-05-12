#pragma once
#include "Object.h"
#include "Components/SpriteAnimation.h"
#include "PotalOut.h"
#include "Player.h"

using namespace ENGINE;
class Potal : public Object
{
	enum class DATA { SPRITE_X = 3, SPRITE_Y = 1 };

private:
	SpriteAnimation* m_animation;
	PotalOut* m_PotalOut;

public:
	Potal();
	virtual ~Potal();
	void Initialize(float portal_In_X, float portal_In_Y,float portal_Out_X, float portal_Out_Y);
	void Draw();
	bool Update(const float& deltaTime);
	bool ApplyCollideEffect(Player* Player);
};