#include "Door.h"
Door::Door()
{
	ResourceMgr->Load("Door.bmp");
	m_renderer = new SpriteRenderer("Door.bmp",(int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
	m_renderer->SetScale(transform->scale.x, transform->scale.y);
	AddComponent(m_renderer);

	m_animation = new SpriteAnimation((int)DATA::SPRITE_X, (int)DATA::SPRITE_Y);
	AddComponent(m_animation);

	m_bIsEnable = true;
}
void Door::Initialize(float x,float y)
{
	transform->position = { x,y };
	m_renderer->Operate(this);
}
void Door::Draw()
{
	m_renderer->Draw();
}
bool Door::CollideCheck(RECT rect, Player* player)
{
	if (m_bIsEnable)
	{
		m_ObjectRect = GetRect();
		Item* playeritem = player->GetItem();
		if (playeritem != nullptr && playeritem->GetItemName() == ITEM_NAME::KEY && playeritem->GetItemState() == ITEM_STATE::USE)
		{
			RECT collideRect;
			if (IntersectRect(&collideRect, &rect, &m_ObjectRect))
			{
				return ApplyCollideEffect(player);
			}
			else
			{
				player->GetItem()->SetItemState(ITEM_STATE::HAS);
				player->GetLRInput()->SetItemState(ITEM_STATE::HAS);
			}
		}
		
	}
	return false;
}
void Door::SetDoorType(DOOR_TYPE type)
{ 
	m_renderer->SetSrc((int)type, 0);
	m_renderer->Operate(this);
}
bool Door::ApplyCollideEffect(Player* player)
{
	Item* playeritem = player->GetItem();
	if (playeritem !=nullptr && playeritem->GetItemName() == ITEM_NAME::KEY&& playeritem->GetItemState() == ITEM_STATE::USE)
	{
		SetDoorType(DOOR_TYPE::OPEN);		//문열린 이미지로 변경

		player->GetItem()->SetIsEnable(false);	//열쇠 사용한거처럼 열쇠 이미지 제거
		return true;
	}
	return false;
}