#pragma once
#include "EngineMecro.h"
#include "ResourceManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "Object.h"
#include "Player.h"
using namespace ENGINE;

enum class GROUND_SIZE { SIZE_SMALL = 1, SIZE_BIG = 2 };
enum class GROUND_IMAGE{IMAGE_LEFT = 0,IMAGE_MIDDLE,IMAGE_RIGHT, IMAGE_ONE,IMAGE_COUNT};
class Ground : public GameObject
{
	
	enum Data { SpritesX = 3, SpritesY = 1,weight = 2};
private:
protected:
	Bitmap* m_arrImage[(int)GROUND_IMAGE::IMAGE_COUNT];
	SIZE m_Size = {0,0};
	std::vector<Bitmap*> m_vecImage;
	RECT m_rect;
	bool m_bIsMove;
public:
	void Initialize(float x, float y,int divide = 0, GROUND_SIZE size = GROUND_SIZE::SIZE_BIG);
	Ground();
	RECT GetRect();
	bool GetIsMove() { return m_bIsMove; }

	virtual void Draw();
	virtual void CollideCheck(Player* player);
	virtual void Update(const float& deltaTime);
	void Reset();
	void Release();

};