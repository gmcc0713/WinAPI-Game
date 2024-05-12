#pragma once
#include "Object.h"
#include "Components/SpriteAnimation.h"
#include "TimeManager.h"
#include "Player.h"

#define SPEED 0.5f

using namespace ENGINE;
enum class TRAP_DIRECTION {UP = 0,DOWN =1};
class WoodTrap : public Object
{
	enum class DATA { SPRITE_X = 2, SPRITE_Y = 2};

private:
	SpriteAnimation* m_animation;
	bool m_bIsTrapWork;		//나무트랩이 올라왔는지 확인
	TRAP_DIRECTION m_TrapDirection;
public:
	WoodTrap(TRAP_DIRECTION direction);
	virtual ~WoodTrap();
	virtual void Initialize(float x,float y)override;;
	virtual void Draw() override;;
	virtual bool Update(const float& deltaTime) override;
	virtual bool ApplyCollideEffect(Player* Player)override;;
};

