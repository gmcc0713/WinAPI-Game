#include "Potal.h"
Potal::Potal()
{
	ResourceMgr->Load("Portal_In.bmp");

	m_renderer = new SpriteRenderer("Portal_In.bmp", (int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);

	AddComponent(m_renderer);

	m_animation = new SpriteAnimation((int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	AddComponent(m_animation);
	m_bIsEnable = true;
}
void Potal::Initialize(float portal_In_X, float portal_In_Y, float portal_Out_X, float portal_Out_Y)
{
	transform->position = { portal_In_X ,portal_In_Y };

	m_PotalOut = new PotalOut;
	m_PotalOut->Initialize(portal_Out_X, portal_Out_Y);
}
void Potal::Draw()
{
	m_renderer->Draw();

	m_PotalOut->Draw();
}
bool Potal::Update(const float& deltaTime)
{
	Operate(this);

	m_animation->Play(0);

	m_PotalOut->Update();
	return false;
}
Potal::~Potal()
{
	delete m_PotalOut;
}

bool Potal::ApplyCollideEffect(Player * Player)
{
	
	Player->SetPosition(m_PotalOut->GetTransform()->position);
	return false;
}