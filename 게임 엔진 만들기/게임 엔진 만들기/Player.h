#pragma once
#include "Character.h"
#include "Components/PlayerInput.h"
#include "UIManager.h"
#include "Item.h"
using namespace ENGINE;

class Player : public Character
{
private:
	enum Data { SpritesX =4, SpritesY = 2, Speed = 200, JUMP_VALUE=400, GRAVITY = 220,WEIGHT = 1 };
	
	Item* m_Item;
	PlayerInput* input;
	bool m_bPlayerNonDamage;		//�÷��̾� ��������

	int m_iLife;
	int m_iTime;
	std::string m_strName;
public:
	Player();

	// GameObject��(��) ���� ��ӵ�
	virtual void SetScale(const Vector2& scale) override;

	RECT GetRect() { return m_CharacterRect; }
	
	void Initialize(float x = 0, float y = 0);
	virtual void Release() override;
	virtual bool Update(const float& deltaTime) override;// �������� ���Ǿ����� true
	virtual void Reset() override;
	virtual void GroundCollideEffectSet(COLLIDE_DIRECTION direction, RECT collideRect);
	virtual void Draw() override;

	std::string GetName() { return m_strName; }
	int GetTime() { return m_iTime; }
	int GetLife() { return m_iLife; }
	PlayerInput* GetLRInput() { return input; }
	Item* GetItem() { return m_Item; }

	void SetTime(int time) { m_iTime = time; }
	void SetName(std::string name) { m_strName = name; }
	void SetLife(int life) { m_iLife = life; }
	
	
	void Jump(const float& deltaTime);

	void PlayerItemUpdate();
	void AddItem(Item* item);
	bool UseItem();
	void DropItem();
	bool MinusLife();

	bool CollideObstacle();		//�÷��̾ ������ return true ���� life�� ���������� return false
};
