#include "SmallGround.h"
SmallGround::SmallGround()
{
    for (int i = 0; i < (int)GROUND_IMAGE::IMAGE_COUNT; i++)
    {
        m_arrImage[i] = ResourceMgr->GetBitmap("SmallGround_" + std::to_string(i + 1) + ".bmp");
        m_arrImage[i]->SetPivot(Pivot::Left | Pivot::Bottom);
    }

    m_Size = m_arrImage[0]->GetSize();
    m_bIsMove = false;
}
void SmallGround::Initialize(float x, float y, int divide = 0)
{
    transform->position = { x, y };

    switch (divide)
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
        for (int i = 0; i < divide - 2; i++)
            m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_MIDDLE]);
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_RIGHT]);
        break;
    }

    m_Size.cx = m_arrImage[0]->GetSize().cx * 0.5f;      //������ ����
    m_Size.cy = m_arrImage[0]->GetSize().cy * 0.5f;

    m_Size.cx *= divide;
}