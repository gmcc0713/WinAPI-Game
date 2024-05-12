#include "MonsterBat.h"
MonsterBat::MonsterBat()
{
    
    ResourceMgr->Load("Monster_Bat.bmp");

    m_renderer = new SpriteRenderer("Monster_Bat.bmp", SpritesX, SpritesY);
    m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
    m_renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(m_renderer);

    AddComponent(m_animation = new SpriteAnimation(SpritesX, SpritesY));
    m_bIsDraw = true;
    m_eIsDie = false;
}

void MonsterBat::Draw()
{
    if (m_bIsDraw)
    {
        m_renderer->Draw();
    }
}
void MonsterBat::Initialize(float start_x, float start_y, float end_x, float end_y)
{
    transform->position = { start_x, start_y };
    m_StartMovePoint = { start_x ,start_y };
    m_EndMovePoint = { end_x ,end_y };
    m_eMoveDirection = MOVE_DIRECTION::RIGHT;
}
bool MonsterBat::Update(const float& deltaTime)
{
    Operate(this);

    AutoMove(deltaTime);

    transform->position.y += GRAVITY * deltaTime;           //중력적용

    if (transform->position.x < m_StartMovePoint.x)
        m_eMoveDirection = MOVE_DIRECTION::RIGHT;
    else if (transform->position.x + m_renderer->GetDrawSize().cx > m_EndMovePoint.x)
        m_eMoveDirection = MOVE_DIRECTION::LEFT;

    return m_eIsDie;
}
MonsterBat::~MonsterBat()
{

}