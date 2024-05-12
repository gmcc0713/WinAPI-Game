#include "Character.h"


void Character::SettingRect()
{
    m_CharacterRect = { (int)transform->position.x,            //피봇이 left,bottom인 사각형 세팅
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
        if (CollideRect.right - CollideRect.left > (m_CharacterRect.right - m_CharacterRect.left) * 0.2f)     //충돌된 범위가 플레이어의 너비*0.2 만큼보다 큰 크기일때 위아래,작을때는 좌우 
        {
            if (CollideRect.bottom < rect.bottom)   //ground위에 플레이어가 있을때
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_UP, CollideRect);
            }
            else  if (CollideRect.top > rect.top)       //ground아래에 플레이어가 있을때
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_DOWN, CollideRect);
            }
        }
        else
        {
            if (CollideRect.right < rect.right) //오른쪽의 벽과 충돌했을때
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_RIGHT, CollideRect);
            }
            else  if (CollideRect.left > rect.left) ////왼쪽의 벽과 충돌했을때
            {
                GroundCollideEffectSet(COLLIDE_DIRECTION::GROUND_LEFT, CollideRect);
            }
        }
    }
}