#include "FireBall.h"
#include "Player.h"
FireBall::FireBall()
{
    m_renderer = new SpriteRenderer("FireBall.bmp");
    m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
    m_renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(m_renderer);

    m_fMoveDistance = (float)DATA::DISTANCE;
}
void FireBall::Initialize(float x, float y, DIRECTION direction)
{
    transform->position = { x,y };
    m_eDirection = direction;
}
bool FireBall::Update(const float &deltaTime)
{
    Operate(this);

    switch (m_eDirection)
    {
    case DIRECTION::LEFT:
        transform->position.x -= (float)DATA::MOVE_SPEED * deltaTime;
        break;
    case DIRECTION::RIGHT:
        transform->position.x += (float)DATA::MOVE_SPEED * deltaTime;
        break;
    }
    m_fMoveDistance-= (float)DATA::MOVE_SPEED * deltaTime;

    if (m_fMoveDistance <= 0|| transform->position.x<=10||transform->position.x>=SceneMgr->GetWidth()-10)
        return true;
    return false;


}
void FireBall::Draw()
{
	m_renderer->Draw();
}
bool FireBall::CollideCheck(RECT rect,Player* player)
{
    RECT collideRect; 
    m_ObjectRect = GetRect();

    if (IntersectRect(&collideRect, &rect, &m_ObjectRect))
    {
        player->MinusLife(); 
    }
    return true;
}