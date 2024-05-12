#pragma once
#include"EngineMecro.h"
#include "Object.h"
#include "Monster.h"
enum class ITEM_NAME {BOMB,KEY};
class Player;
class Item : public Object
{
protected:
	ITEM_NAME m_eName;				//�������� ��������������
	ITEM_STATE m_eItemState;		//�������� �ʵ忡�ִ»�������, �������ִ� ��������, ����������
	bool m_bIsItemEffect;			//�������� ���ǰ� ȿ�� ����������� �ƴ���
public:
	void SetItemState(ITEM_STATE state) { m_eItemState = state; }
	void SetItemPosY(float y);

	ITEM_STATE GetItemState() { return m_eItemState; }
	ITEM_NAME GetItemName() { return m_eName; }
	bool GetIsEffectSet() 
	{ 
		return m_bIsItemEffect; 
	}
	void MoveItemWithPlayer(Vector2 transform);//�÷��̾ �������� ������ ������ �÷��̾��� �����Ӱ� ���� ������
	bool CollideCheck(Player* player);						//�ʵ忡 ������ �÷��̾�� �浹üũ
	virtual bool EffectCollideCheck(Player* player) = 0;
	virtual bool Update(const float& deltaTime) = 0;
};

