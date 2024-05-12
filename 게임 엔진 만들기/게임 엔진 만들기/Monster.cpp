#include "Monster.h"
#include "Player.h"
void Monster::Release()
{

}
void Monster::Reset()
{

}
void Monster::AutoMove(const float& deltaTime)
{
    switch (m_eMoveDirection)
    {
    case MOVE_DIRECTION::LEFT:
        m_animation->Play(1);
        transform->position.x -= Speed * deltaTime;
        break;
    case MOVE_DIRECTION::RIGHT:
        m_animation->Play(0);
        transform->position.x += Speed * deltaTime;
        break;
    }
}
void Monster::GroundCollideEffectSet(COLLIDE_DIRECTION direction, RECT collideRect) 
{
    switch (direction)
    {
    case COLLIDE_DIRECTION::GROUND_UP:
        transform->position.y -= collideRect.bottom - collideRect.top;
        break;
    case COLLIDE_DIRECTION::GROUND_DOWN:
        transform->position.y += collideRect.bottom - collideRect.top;
        break;
    case COLLIDE_DIRECTION::GROUND_LEFT:
        transform->position.x += collideRect.right - collideRect.left;
        m_eMoveDirection = MOVE_DIRECTION::RIGHT;
        break;
    case COLLIDE_DIRECTION::GROUND_RIGHT:
        transform->position.x -= collideRect.right - collideRect.left;
        m_eMoveDirection = MOVE_DIRECTION::LEFT;
        break;
    }
}
void Monster::PlayerCollideCheck(Player* player)
{
    RECT collideRect,playerRect = player->GetRect();
    SettingRect();

    if (IntersectRect(&collideRect, &playerRect, &m_CharacterRect))
    {
        player->MinusLife();
    }
}
bool Monster::CollideObstacle()
{
    m_bIsDraw = false;
    m_eIsDie = true;
    return true;
}
