#include "Item.h"
#include "Player.h"
bool Item::CollideCheck(Player* player)
{	
	m_ObjectRect = GetRect();
	RECT collideRect;
	RECT playerRect = player->GetRect();
	switch (m_eItemState)
	{
		case ITEM_STATE::FIELD:
		{
			if (m_bIsEnable&&IntersectRect(&collideRect, &playerRect, &m_ObjectRect))
			{
				player->AddItem(this);
			}
			break;
		}
		case ITEM_STATE::USE:
		{
			return EffectCollideCheck(player);
		}
	}

	return false;
}

void Item::SetItemPosY(float y)
{
	transform->position.y = y;
}
void Item::MoveItemWithPlayer(Vector2 pos)
{
	if (m_eItemState == ITEM_STATE::HAS)
	{
		transform->position = pos;
	}
}

