#include "MonsterSnake.h"
#include "Player.h"
MonsterSnake::MonsterSnake()
{

    ResourceMgr->Load("Monster_Snake.bmp");

    m_renderer = new SpriteRenderer("Monster_Snake.bmp", SpritesX, SpritesY);
    m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
    m_renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(m_renderer);

    AddComponent(m_animation = new SpriteAnimation(SpritesX, SpritesY));
    m_bIsDraw = true;
    m_eIsDie = false;

    m_fTimer = 0;
    m_fFrameRate = 3;
}

void MonsterSnake::Draw()
{

    if (m_bIsDraw)
    {
        m_renderer->Draw();
    }
    for (FireBall* fireball : m_vecFireball)
    {
        fireball->Draw();
    }

}
void MonsterSnake::Initialize(float start_x, float start_y, float end_x, float end_y)
{
    transform->position = { start_x, start_y };
    m_StartMovePoint = { start_x ,start_y };
    m_EndMovePoint = { end_x ,end_y };

    m_eMoveDirection = MOVE_DIRECTION::RIGHT;
}
bool MonsterSnake::Update(const float& deltaTime)
{
    Operate(this);
    
    AutoMove(deltaTime);

    transform->position.y += GRAVITY * deltaTime;           //중력적용

    if (transform->position.x < m_StartMovePoint.x)
        m_eMoveDirection = MOVE_DIRECTION::RIGHT;
    else if (transform->position.x + m_renderer->GetDrawSize().cx > m_EndMovePoint.x)
        m_eMoveDirection = MOVE_DIRECTION::LEFT;
  
    MakeFireBall();

    UpdateFireBall(deltaTime);

    return m_eIsDie;
}
void MonsterSnake::MakeFireBall()
{
    m_fTimer += TimeMgr->DeltaTime();	//소요된 시간 * 속도
    if (m_fFrameRate <= m_fTimer)
    {
        float fireball_X;
        switch (m_eMoveDirection)
        {
        case MOVE_DIRECTION::RIGHT:
            fireball_X = transform->position.x + m_renderer->GetDrawSize().cx * 0.9f;
            break;
        case MOVE_DIRECTION::LEFT:
            fireball_X = transform->position.x;
            break;
        }

        FireBall* fireball = new FireBall;
        fireball->Initialize(fireball_X, transform->position.y - m_renderer->GetDrawSize().cy*0.9f, (DIRECTION)m_eMoveDirection);
        m_vecFireball.push_back(fireball);

        m_fTimer -= m_fFrameRate;
    }
}
void MonsterSnake::UpdateFireBall(const float& deltaTime)
{
    for (auto iter = m_vecFireball.begin(); iter != m_vecFireball.end();)
    {
        if ((*iter)->Update(deltaTime))
        {
            delete* iter;
           iter = m_vecFireball.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}
void MonsterSnake::PlayerCollideCheck(Player* player)
{
    RECT collideRect, playerRect = player->GetRect();
    SettingRect();

    if (IntersectRect(&collideRect, &playerRect, &m_CharacterRect))
    {
        player->MinusLife();
    }
    for (FireBall* fireball : m_vecFireball)
    {
        fireball->CollideCheck(playerRect, player);
    }
}
MonsterSnake::~MonsterSnake()
{
    for (FireBall* fireball : m_vecFireball)
    {
        delete fireball;
    }
}