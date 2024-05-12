#pragma once
#include "EngineMecro.h"
#include"Components/SpriteRenderer.h"
#include"Components/SpriteAnimation.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Object.h"

class Player;
using namespace ENGINE;

enum class DIRECTION { RIGHT = 0, LEFT, NONE };
enum class DATA { MOVE_SPEED = 300, DISTANCE = 600 };
class FireBall : public Object
{
private:
	DIRECTION m_eDirection;
	float m_fMoveDistance;
public:
	FireBall();
	bool CollideCheck(RECT rect, Player* player);
	void Initialize(float x, float y, DIRECTION direction);
	bool Update(const float& deltaTime);
	void Draw();
};

