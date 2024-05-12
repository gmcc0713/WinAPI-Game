#include "Box.h"
Box::Box()
{

	m_renderer = new SpriteRenderer("Box.bmp");
	m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);

	AddComponent(m_renderer);

	m_iWeight = 0;
	m_bIsMove = true;
}

void Box::Initialize(float x,float y)
{
	transform->position = { x,y };
	Operate(this);
}
void Box::Draw()
{
	m_renderer->Draw();
}
void Box::Update(const float& deltaTime)
{
	Operate(this);
}
void Box::CollideCheck(Player* Player)
{
	GetRect();
	RECT collideRect;
	RECT playerRect = Player->GetRect();
	Player->MoveAssist(m_rect,true);

	if (IntersectRect(&collideRect, &m_rect, &playerRect))
	{
		transform->position.x += 100;
		Operate(this);
	}
}

Box::~Box()
{

}