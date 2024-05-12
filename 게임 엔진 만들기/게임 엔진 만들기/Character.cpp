#include "Character.h"


void Character::SettingRect()
{
    m_CharacterRect = { (int)transform->position.x,            //�Ǻ��� left,bottom�� �簢�� ����
                  (int)transform->position.y - m_renderer->GetDrawSize().cy,
                    (int)transform->position.x + m_renderer->GetDrawSize().cx
                  ,(int)transform->position.y };

}
bool Character::CollideCheck(RECT rect)
{
    RECT collideRect;
    SettingRect();

    if (IntersectRect(&collideRect, &rect, &m_CharacterRect))
    {
        if (CollideObstacle())
        {
            return true;
        }
    }
    return false;
}
void Character::GroundCollideDirectionCheck(RECT rect)
{
    RECT CollideRect;
    if (IntersectRect(&CollideRect, &rect, &m_CharacterRect))
    {
        if (CollideRect.right - CollideRect.left > (m_CharacterRect.right - m_CharacterRect.left) * 0.2f)     //�浹�� ������ �÷��̾��� �ʺ�*0.2 ��ŭ���� ū ũ���϶� ���Ʒ�,�������� �¿� 
        {
            if (CollideRect.bottom < rect.bottom)   //ground���� �÷��̾ ������
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_UP, CollideRect);
            }
            else  if (CollideRect.top > rect.top)       //ground�Ʒ��� �÷��̾ ������
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_DOWN, CollideRect);
            }
        }
        else
        {
            if (CollideRect.right < rect.right) //�������� ���� �浹������
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_RIGHT, CollideRect);
            }
            else  if (CollideRect.left > rect.left) ////������ ���� �浹������
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_LEFT, CollideRect);
            }
        }
    }
}