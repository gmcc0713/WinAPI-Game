#include "Player.h"
#include "SceneManager.h"


Player::Player()
{
    ResourceMgr->Load("Player.bmp");
    
    m_renderer = new SpriteRenderer("Player.bmp", SpritesX, SpritesY);
    m_renderer->SetPivot(Pivot::Left | Pivot::Bottom);
    m_renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(m_renderer);

    AddComponent(m_animation = new SpriteAnimation(SpritesX, SpritesY));
    AddComponent(input = new PlayerInput);
   
    m_iLife = 3;
    m_Item = nullptr;
    m_bPlayerNonDamage = false;
    m_bIsDraw = true;
}

void Player::Draw()
{
    if (m_bIsDraw)
    {
        m_renderer->Draw();
    }

}

void Player::SetScale(const Vector2& scale)
{
    GameObject::SetScale(scale);
    if (m_renderer) m_renderer->SetScale(scale.x, scale.y);
}

void Player::Initialize(float x, float y)
{
    transform->position = { 0, 500 };
}

void Player::Release()
{

}  

bool Player::Update(const float& deltaTime)
{
    Operate(this);

    switch (input->GetDirection())
    {
    case PlayerInput::Direction::Left:
        m_animation->Play(1); 
        transform->position.x -= Speed * deltaTime;
        break;
    case PlayerInput::Direction::Right:
        m_animation->Play(0);
        transform->position.x += Speed * deltaTime;
        break;
    default: m_animation->Stop(); break;
    }

    if (m_Item)
    {
        m_Item->MoveItemWithPlayer({ transform->position.x, transform->position.y - m_renderer->GetDrawSize().cy * 0.8f });
    }

    Jump(deltaTime);     //점프 처리

    SettingRect();      //이동한 거리 저장

    PlayerItemUpdate();

    if (m_bPlayerNonDamage)     //무적상태일때
    {
        m_fTimer += deltaTime;      
        m_bIsDraw = !m_bIsDraw;  //깜빡거림을 위한 변경
        if (m_fTimer >= 2)      //무적시간 끝날때
        {
            m_bPlayerNonDamage = false; 
            m_bIsDraw = true;
            m_fTimer = 0;
        }
    }

    if (m_iLife <= 0)
    {
        return true;
    }
    return false;
}
void Player::AddItem(Item* item)
{
    if (input->GetIsPressDropItem())
    {

        m_Item = item;
        m_Item->SetPosition({ transform->position.x, transform->position.y - m_renderer->GetDrawSize().cy*0.8f });
        m_Item->SetItemState(ITEM_STATE::HAS);

        input->SetItemState(ITEM_STATE::HAS);
        input->SetIsPressDropItem(false);               //아이템 줍기/떨어뜨리기 false로 변경
    }
}
void Player::PlayerItemUpdate()
{
    if (!m_Item) return;
    switch (input->GetItemState())
    {
    case ITEM_STATE::HAS:
        m_Item->Operate(m_Item);
        if (input->GetIsPressDropItem())
        {
            DropItem();
        }
        break;

    case ITEM_STATE::USE:

        UseItem();
        return;
    }

}
void Player::DropItem()
{
    if (input->GetItemState() == ITEM_STATE::HAS && input->GetIsPressDropItem())    //아이템 보유하면서 아이템 줍기/떨어뜨리기 버튼이 눌러졌을때
    {
        m_Item->SetItemState(ITEM_STATE::FIELD);          //아이템 사용 상태로 변경
        m_Item->SetItemPosY(transform->position.y);     //아이템 바닥에 떨어뜨리기

        input->SetItemState(ITEM_STATE::NONE);
        input->SetIsPressDropItem(false);               //아이템 줍기/떨어뜨리기 false로 변경
    }
}
bool Player::UseItem()       //아이템 사용상태로 변경
{
    if (input->GetItemState() == ITEM_STATE::USE)       //인풋에서 아이템을 사용했을때
    {
        m_Item->SetItemState(ITEM_STATE::USE);          //아이템 사용 상태로 변경
        m_Item->SetItemPosY(transform->position.y);     //아이템 바닥에 떨어뜨리기

        input->SetItemState(ITEM_STATE::NONE);          //인풋에서 아이템을 NONE상태로 변경
        return true;
    }
    return false;
}

void Player::GroundCollideEffectSet(COLLIDE_DIRECTION direction,RECT collideRect)
{
    switch (direction)
    {
    case COLLIDE_DIRECTION::GROUND_UP:
        transform->position.y -= collideRect.bottom - collideRect.top;
        input->SetJumpState(PlayerInput::JUMP_STATE::NONE);
        break;
    case COLLIDE_DIRECTION::GROUND_DOWN:
        transform->position.y += collideRect.bottom - collideRect.top;
        input->SetJumpState(PlayerInput::JUMP_STATE::DOWN);
        break;
    case COLLIDE_DIRECTION::GROUND_LEFT:
        transform->position.x += collideRect.right - collideRect.left;
        break;
    case COLLIDE_DIRECTION::GROUND_RIGHT:
        transform->position.x -= collideRect.right - collideRect.left;
        break;
    }

}

void Player::Reset()
{
    transform->position = { 0, 500 };
    m_Item = nullptr;
    m_bPlayerNonDamage = false;
    m_bIsDraw = true;
    input->Reset();
}

void Player::Jump(const float& deltaTime)
{
        switch (input->GetJumpState())
        {
        case PlayerInput::JUMP_STATE::UP:

            transform->position.y -= (JUMP_VALUE-GRAVITY) * deltaTime; 

            if (transform->position.y <= input->GetJumpHeight())
            {
                input->SetJumpState(PlayerInput::JUMP_STATE::DOWN);
            }

            break;
        default:

            transform->position.y += GRAVITY * deltaTime;

            if (transform->position.y >= SceneMgr->GetHeight())
            {
                m_iLife = 0;
            }
            break;
        }
}

bool Player::CollideObstacle()
{
    return MinusLife();
}
bool Player::MinusLife()
{
    if (!m_bPlayerNonDamage)
    {
        m_bPlayerNonDamage = true;
        m_iLife--;
        if (m_iLife <= 0)
        {
            return true;
        }
    }
    return false;
}