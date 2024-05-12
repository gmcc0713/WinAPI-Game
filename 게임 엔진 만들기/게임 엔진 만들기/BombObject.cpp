#include "BombObject.h"
#include "Player.h"
BombObject::BombObject()
{
	ResourceMgr->Load("Bomb.bmp");
	m_renderer = new SpriteRenderer("Bomb.bmp", (int)Data::SpritesX, (int)Data::SpritesY);
	m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);
	m_animation = new SpriteAnimation((int)Data::SpritesX, (int)Data::SpritesY);

	AddComponent(m_renderer);
	AddComponent(m_animation);

	m_bIsEnable = true;
	m_eItemState = ITEM_STATE::FIELD;
	m_eName = ITEM_NAME::BOMB;
	m_bIsItemEffect = false;		
	m_fTimer = 0;
	m_fFrameRate = 2;
}

void BombObject::Initialize(float x, float y)
{
	transform->position = { x,y };
	m_renderer->Operate(this);
}

void BombObject::Draw()
{
	if (m_bIsEnable)
	{
		m_renderer->Draw();
	}
	if (m_BombEffect.GetEnable())
	{
		m_BombEffect.Draw();
	}

}

bool BombObject::Update(const float & deltaTime)
{
	Operate(this);


	switch (m_eItemState)
	{
	case ITEM_STATE::USE:

		if (m_bIsEnable)
		{
			m_animation->Play(0);

			m_fTimer += TimeMgr->DeltaTime();	//소요된 시간 * 속도
			if (m_fFrameRate <= m_fTimer)
			{
				m_fTimer -= m_fFrameRate;
				m_bIsEnable = false;
				m_bIsItemEffect = true;

				m_BombEffect.Start(transform->position.x, transform->position.y);
			}
		}
		if (m_BombEffect.Update(deltaTime))
			m_eItemState = ITEM_STATE::NONE;
	}

	if (m_eItemState == ITEM_STATE::NONE)
		return true;
	return false;
}
bool BombObject::EffectCollideCheck(Player* player)
{
	if (m_bIsItemEffect)
	{
		if (player->CollideCheck(m_BombEffect.GetRect()))
			return true;
	}
}