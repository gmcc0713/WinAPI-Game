#include "Object.h"
#include "Player.h"
Object::Object()
{

}

bool Object::CollideCheck(RECT rect, Player* player)
{
	m_ObjectRect = GetRect();
	if (m_bIsEnable)
	{
		RECT collideRect;
		if (IntersectRect(&collideRect, &rect, &m_ObjectRect))
		{
			return ApplyCollideEffect(player);
		}
	}
	return false;
}

RECT Object::GetRect()
{
	RECT rect = {  (int)transform->position.x,            //�Ǻ��� left,bottom�� �簢�� ����
					(int)transform->position.y - m_renderer->GetDrawSize().cy,
					  (int)transform->position.x + m_renderer->GetDrawSize().cx
					,(int)transform->position.y };
	return rect;
}