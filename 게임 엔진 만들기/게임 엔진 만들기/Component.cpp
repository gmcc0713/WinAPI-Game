#include "EngineMecro.h"

namespace ENGINE
{
    VOID Transform::Reset()
    {
        position.x = position.y = 0.0f;
        scale.x = scale.y = 1.0f;
    }

	GameObject::GameObject()
	{
		transform = new Transform;
		AddComponent(transform);			//transform 추가
	}
	GameObject::~GameObject()
	{
		for (std::pair<ComponentType, Component*> c : components) DEL(c.second);
	}
	Component* GameObject::GetComponent(CONST ComponentType& type)
	{
		auto iter = components.find(type);				//components 에서 해당 Component 찾기
		if (components.end() != iter) return iter->second;	//찾으면 해당 값 return

		return nullptr;
	}
	BOOL GameObject::AddComponent(Component* component)
	{
		if (!component || GetComponent(component->GetType())) return FALSE;			//component가 비어있거나 게임오브젝트일시 false  return
		components.insert(std::make_pair(component->GetType(), component));			//아니면 components에 삽입
		return TRUE;
	}
    VOID GameObject::Operate(GameObject* Owner)
    {
        for (std::pair<ComponentType, Component*> c : components) c.second->Operate(this);
    }
    VOID GameObject::Reset()
    {
        for (std::pair<ComponentType, Component*> c : components) c.second->Reset();
    }

	VOID AnimationComponent::SetSpeed(FLOAT speed)
	{
		isReverse = (0 > speed);
		this->speed = std::abs(speed);
	}
}