#pragma once
#include "Object.h"
#include "Components/SpriteAnimation.h"
#include "Player.h"
using namespace ENGINE;

enum class DOOR_TYPE {CLOSE=0, OPEN = 1};

class Door : public Object
{
	enum class DATA {SPRITE_X=2,SPRITE_Y = 1};
private:
	SpriteAnimation* m_animation;

public:
	Door();
	bool CollideCheck(RECT rect, Player* player);
	bool ApplyCollideEffect(Player* player);
	void Initialize(float x, float y);
	void SetDoorType(DOOR_TYPE type);
	void Draw();

};

