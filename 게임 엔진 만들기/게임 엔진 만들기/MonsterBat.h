#pragma once
#include "Monster.h"
class MonsterBat: public Monster
{
private:
public:
	MonsterBat();
	~MonsterBat();
	virtual void Initialize(float start_x, float start_y, float end_x, float end_y)override;	//�ڵ� �̵� ���۰� ����ġ
	virtual void Draw() override;
	virtual bool Update(const float& deltaTime) override;
};

