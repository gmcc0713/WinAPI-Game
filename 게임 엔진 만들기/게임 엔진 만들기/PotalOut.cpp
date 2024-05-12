#include "PotalOut.h"
PotalOut::PotalOut()
{
	ResourceMgr->Load("Portal_Out.bmp");

	m_renderer = new SpriteRenderer("Portal_Out.bmp", (int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);

	AddComponent(m_renderer);

	m_animation = new SpriteAnimation((int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	AddComponent(m_animation);
}
void PotalOut::Initialize(float x, float y)
{
	transform->position = { x,y };
}
void PotalOut::Update()
{
	m_animation->Play(0);
}
void PotalOut::Draw()
{
	Operate(this);

	m_renderer->Draw();
}
