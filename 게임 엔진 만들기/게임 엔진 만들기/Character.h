#pragma once
#include "EngineMecro.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "ResourceManager.h"

using namespace ENGINE;
class Character : public GameObject
{
protected:
	enum class COLLIDE_DIRECTION{ GROUND_LEFT, GROUND_RIGHT,GROUND_UP, GROUND_DOWN};
	SpriteRenderer* m_renderer;
	SpriteAnimation* m_animation;

	RECT m_CharacterRect;
	float m_fTimer;
	bool m_bIsDraw;		

	virtual bool Update(const float& deltatime) = 0;
	virtual void Release() = 0;
	virtual void Draw() = 0;
	virtual void Reset() = 0;
	virtual void GroundCollideEffectSet(COLLIDE_DIRECTION direction, RECT collideRect) = 0;
	virtual bool CollideObstacle() = 0;	

public:
	Character() {}
	void SettingRect();
	RECT GetRect() { SettingRect(); return m_CharacterRect; }
	void GroundCollideDirectionCheck(RECT rect);
	bool CollideCheck(RECT Rect);

};

