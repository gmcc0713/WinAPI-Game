#pragma once
#include "Ground.h"


class Box : public Ground
{
private:
	SpriteRenderer* m_renderer;
	int m_iWeight;
public:
	Box();
	~Box();
	void Initialize(float x, float y);
	void Draw();
	virtual void Update(const float& deltaTime)override;
	void CollideCheck(Player* Player);
};

