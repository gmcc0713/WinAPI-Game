#pragma once
#include"EngineMecro.h"
#include "Object.h"
#include "Monster.h"
enum class ITEM_NAME {BOMB,KEY};
class Player;
class Item : public Object
{
protected:
	ITEM_NAME m_eName;				//아이템이 무슨아이템인지
	ITEM_STATE m_eItemState;		//아이템이 필드에있는상태인지, 가지고있는 상태인지, 사용상태인지
	bool m_bIsItemEffect;			//아이템이 사용되고 효과 적용상태인지 아닌지
public:
	void SetItemState(ITEM_STATE state) { m_eItemState = state; }
	void SetItemPosY(float y);

	ITEM_STATE GetItemState() { return m_eItemState; }
	ITEM_NAME GetItemName() { return m_eName; }
	bool GetIsEffectSet() 
	{ 
		return m_bIsItemEffect; 
	}
	void MoveItemWithPlayer(Vector2 transform);//플레이어가 아이템을 가지고 있을때 플레이어의 움직임과 같이 움직임
	bool CollideCheck(Player* player);						//필드에 있을때 플레이어와 충돌체크
	virtual bool EffectCollideCheck(Player* player) = 0;
	virtual bool Update(const float& deltaTime) = 0;
};

