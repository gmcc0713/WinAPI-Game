#pragma once
#include "Monster.h"
#include "FireBall.h"
class Player;
class MonsterSnake : public Monster
{
private:
	std::vector<FireBall*> m_vecFireball;
	float m_fTimer;
	float m_fFrameRate;
public:
	MonsterSnake();
	~MonsterSnake();
	virtual void Initialize(float start_x, float start_y, float end_x, float end_y) override;	//자동 이동 시작과 끝위치
	virtual void Draw() override;
	virtual bool Update(const float& deltaTime) override;

	void UpdateFireBall(const float& deltaTime);
	void MakeFireBall();
	void PlayerCollideCheck(Player* player);


};

