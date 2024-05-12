#include "../Component.h"

#ifndef LR_INPUT_H
#define LR_INPUT_H

namespace ENGINE
{
	class PlayerInput : public InputComponent
	{
		enum class DATA {JUMP_VALUE = 100};
	public:
		enum class Direction { None = -1, Right = 0, Left = 1, };
		enum class JUMP_STATE { NONE = -1, UP = 0, DOWN = 1}; //NONE - �߷¹޴� ���� up - ������ �ö󰡴� ���� down - ������ �������� ���� walk - �������� �ɾ�ٴϴ� ����
	private:
		Direction dir;
		JUMP_STATE m_jumpState;				//Ű �Է¹����� ������ ����
		ITEM_STATE m_ItemState;				//Ű �Է¹����� ������ ����
		unsigned int left, right, jump , useitem, dropGetItem;
		unsigned int m_iJumpHeight;			//������ �ö󰡴� ��ġ
		bool m_bIsPressDropItem;
	public:
		PlayerInput() : dir(Direction::None), left(VK_LEFT), right(VK_RIGHT),jump(VK_SPACE), useitem(VK_UP), dropGetItem(VK_DOWN), m_jumpState(JUMP_STATE::NONE), m_ItemState(ITEM_STATE::NONE), m_bIsPressDropItem(false){}

		void SetLeftKey(unsigned left) { this->left = left; }
		void SetRightKey(unsigned right) { this->right = right; }
		void SetJumpKey(unsigned int jump) { this->jump = jump; }
		void SetJumpState(JUMP_STATE jumpState) { m_jumpState = jumpState; }
		void SetItemState(ITEM_STATE state) { m_ItemState = state; }
		void SetIsPressDropItem(bool ispress) { m_bIsPressDropItem = ispress; }

		bool GetIsPressDropItem() const { return m_bIsPressDropItem; }
		Direction GetDirection() const { return dir; }
		JUMP_STATE GetJumpState()const { return m_jumpState; }
		ITEM_STATE GetItemState()const { return m_ItemState; }

		unsigned int GetJumpHeight()const { return m_iJumpHeight; }


		// InputComponent��(��) ���� ��ӵ�
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override;
	};
}

#endif // !LR_INPUT_H