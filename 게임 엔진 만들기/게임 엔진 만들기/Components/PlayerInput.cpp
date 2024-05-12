#include "PlayerInput.h"
#include "../InputManager.h"

namespace ENGINE
{
	VOID PlayerInput::Operate(GameObject* Owner)
	{
		if (m_jumpState == JUMP_STATE::NONE && m_ItemState!=ITEM_STATE::HAS)			
		{
			if (ENGINE::InputMgr->GetKeyPressed(jump))
			{
				m_jumpState = JUMP_STATE::UP;
				m_iJumpHeight = Owner->GetTransform()->position.y-(int)DATA::JUMP_VALUE;
			}
		}

		if (ENGINE::InputMgr->GetKeyPressed(left))
		{
			dir = Direction::Left;
		}
		else if (ENGINE::InputMgr->GetKeyPressed(right))
		{
			dir = Direction::Right;
		}
		else dir = Direction::None;
		
		if (m_ItemState == ITEM_STATE::HAS)			
		{
			if (ENGINE::InputMgr->GetKeyPressed(useitem))
			{
				m_ItemState = ITEM_STATE::USE;
			}
		}

		if (ENGINE::InputMgr->GetKeyDown(dropGetItem))
		{
			m_bIsPressDropItem = true;
		}
	}

	VOID PlayerInput::Reset()
	{
		dir = Direction::None;
		m_jumpState = JUMP_STATE::NONE;
		m_ItemState = ITEM_STATE::NONE;
		m_iJumpHeight = 0;
		m_bIsPressDropItem = false;
	}
}