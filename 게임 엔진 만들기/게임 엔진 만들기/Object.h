#pragma once
#include "EngineMecro.h"
#include"Components/SpriteRenderer.h"
#include "ResourceManager.h"


using namespace ENGINE;
class Player;

class Object : public GameObject
{
	enum class OBJECT_TYPE {WALL,ITEM};

private:
protected:
	SpriteRenderer* m_renderer;
	RECT m_ObjectRect;

	bool m_bIsEnable;
public:
	Object();
	RECT GetRect();
	bool GetIsEnable() { return m_bIsEnable; }
	void SetIsEnable(bool enable) { m_bIsEnable = enable; }
	
	virtual void Initialize(float x, float y) {};
	virtual bool CollideCheck(RECT rect,Player* player);
	virtual bool ApplyCollideEffect(Player* player) { return false; }
	virtual bool Update(const float& deltaTime) { Operate(this);  return false; }
	virtual void Draw() = 0;
	void Release() {}

	virtual ~Object(){}
};

