#include "Key.h"
Key::Key()
{
	ResourceMgr->Load("Key.bmp");
	m_renderer = new SpriteRenderer("Key.bmp");
	m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);
	AddComponent(m_renderer);

	m_eItemState = ITEM_STATE::FIELD;
	m_eName = ITEM_NAME::KEY;
	m_bIsItemEffect = true;
	m_bIsEnable = true;
}
void Key::Initialize(float x, float y)
{
	transform->position = { x,y };
	m_renderer->Operate(this);
}

void Key::Draw()
{
	if (m_bIsEnable)
	{
		m_renderer->Draw();
	}

}

bool Key::Update(const float& deltaTime)
{
	Operate(this);


	if (m_eItemState==ITEM_STATE::NONE)
		return true;
	return false;
}
bool Key::EffectCollideCheck(Player* player)
{
	return false;
}