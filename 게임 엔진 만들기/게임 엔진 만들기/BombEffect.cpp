#include "BombEffect.h"

BombEffect::BombEffect()
{
	ResourceMgr->Load("bomb_effects.bmp");
	m_renderer = new SpriteRenderer("bomb_effects.bmp", (int)Data::SpritesX, (int)Data::SpritesY);
	m_renderer->SetPivot(Pivot::Left| Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);

	m_animation = new SpriteAnimation((int)Data::SpritesX, (int)Data::SpritesX);

	AddComponent(m_renderer);
	AddComponent(m_animation);

	m_bEnable = false;
	m_fTimer = 0;
	m_fFrameRate = 0.5f;
}
void BombEffect::Initialize(float x,float y)
{
	transform->position = { x,y };
	m_renderer->Operate(this);
}
void BombEffect::Start(float x, float y)
{
	m_bEnable = true;
	transform->position = { x,y };
	m_renderer->Operate(this);
}
bool BombEffect::Update(float deltaTime)
{
	if (m_bEnable)
	{
		Operate(this);
		m_animation->Play(0);
		m_fTimer += TimeMgr->DeltaTime();	//소요된 시간 * 속도
		if (m_fFrameRate <= m_fTimer)
		{
			m_fTimer -= m_fFrameRate;
			m_bEnable = false;
			m_fTimer = 0;
			return true;
		}
		
	}
	return false;
}
void BombEffect::Draw()
{
	if (m_bEnable)
		m_renderer->Draw();
}
RECT BombEffect::GetRect()
{
	RECT rect = { (int)transform->position.x,            //피봇이 left,bottom인 사각형 세팅
					(int)transform->position.y - m_renderer->GetDrawSize().cy,
					  (int)transform->position.x + m_renderer->GetDrawSize().cx
					,(int)transform->position.y };
	return rect;
}