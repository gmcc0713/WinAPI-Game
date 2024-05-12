#include "WoodTrap.h"
WoodTrap::WoodTrap(TRAP_DIRECTION direction)
{
	ResourceMgr->Load("WoodTrap.bmp");
	m_renderer = new SpriteRenderer("WoodTrap.bmp", (int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);
	AddComponent(m_renderer);

	m_animation = new SpriteAnimation((int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	AddComponent(m_animation);

	m_animation->SetSpeed(SPEED);

	m_bIsEnable = true;
	m_bIsTrapWork = false;

	m_TrapDirection = direction;
}
void WoodTrap::Initialize(float x, float y)
{
	transform->position = { x,y+10 };
}
void WoodTrap::Draw()
{
	m_renderer->Draw();
}
bool WoodTrap:: Update(const float & deltaTime)
{
	Operate(this);
	
	m_animation->Play((int)m_TrapDirection);

	
	if (m_animation->GetIsChange())
	{
		m_bIsTrapWork = !m_bIsTrapWork;
	}


	return false;
}
bool WoodTrap::ApplyCollideEffect(Player* Player)
{
	if (m_bIsTrapWork)
	{
		Player->CollideObstacle();
	}
	return false;
}
WoodTrap::~WoodTrap()
{

}