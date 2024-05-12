#pragma once

#include "Character.h";
#include "TimeManager.h"
using namespace ENGINE;
class Player;
class Monster : public Character
{
protected:
	enum Data { SpritesX = 4, SpritesY = 2, Speed = 200, GRAVITY = 50, };
	enum class MOVE_DIRECTION {RIGHT=0,LEFT,NONE};
	MOVE_DIRECTION m_eMoveDirection;
	bool m_eIsDie;
	Vector2 m_StartMovePoint;
	Vector2 m_EndMovePoint;
public:
	virtual void Initialize(float start_x, float start_y,float end_x,float end_y) = 0;	//자동 이동 시작과 끝위치
	virtual void Draw() = 0;
	virtual bool Update(const float& deltaTime) = 0;	

	void AutoMove(const float& deltaTime);
	virtual void PlayerCollideCheck(Player* player);
	virtual void Release() override;
	virtual void Reset() override;
	virtual void GroundCollideEffectSet(COLLIDE_DIRECTION direction, RECT collideRect);
	virtual bool CollideObstacle() override;		//항상 return true;
	
};

