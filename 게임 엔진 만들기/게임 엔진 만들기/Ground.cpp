#include "Ground.h"
Ground::Ground()
{

}
RECT Ground::GetRect()      //�Ǻ��� Left Bottom �϶�
{
    m_rect = { (int)transform->position.x,       
                    (int)transform->position.y - m_Size.cy,
                      (int)transform->position.x + m_Size.cx
                    ,(int)transform->position.y };
    return m_rect;
}
void Ground::Draw()
{
    int count = 0;
    for (Bitmap* image : m_vecImage)
    {
        image->TransparentBlt(transform->position.x+m_arrImage[0]->GetSize().cx*count, transform->position.y);
        count++;
    }
}
void Ground::Update(const float & deltaTime)
{
    Operate(this);
}
void Ground::Initialize(float x, float y,int tile_x_count, GROUND_SIZE size)      //ground���� x,y,����(ũ��� 100,100),SmallGround�� 5050
{ 
    transform->position = { x, y };
    std::string str = "";

    if (size == GROUND_SIZE::SIZE_SMALL)        //small ground�϶�
    {
        str = "Small";
    }

    for (int i = 0; i < (int)GROUND_IMAGE::IMAGE_COUNT; i++)
    {
        m_arrImage[i] = ResourceMgr->GetBitmap(str+"Ground_" + std::to_string(i + 1) + ".bmp");
        m_arrImage[i]->SetPivot(Pivot::Left | Pivot::Bottom);
    }
    switch (tile_x_count)
    {
    case 0:
        return;
    case 1:     //Ground�� �Ѱ��϶�
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_ONE]);
        break;
    case 2:     //Ground�� �ΰ��϶�
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_LEFT]);
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_RIGHT]);
        break;
    default:        //Ground�� �����̻��϶�
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_LEFT]);
        for(int i =0;i< tile_x_count-2;i++)
            m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_MIDDLE]);
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_RIGHT]);
        break;
    }

    m_Size= m_arrImage[0]->GetSize();      //������ ����

    m_Size.cx *= tile_x_count;
    m_bIsMove = false;
}

void Ground::Reset()
{
    m_vecImage.clear();
    m_Size = { 0,0 };
}
void Ground::Release()
{

}
void Ground::CollideCheck(Player* player)
{

}
