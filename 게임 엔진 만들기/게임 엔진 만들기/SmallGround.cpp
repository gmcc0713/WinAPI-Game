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
    case 1:     //Ground가 한개일때
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_ONE]);
        break;
    case 2:     //Ground가 두개일때
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_LEFT]);
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_RIGHT]);
        break;
    default:        //Ground가 세개이상일때
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_LEFT]);
        for (int i = 0; i < divide - 2; i++)
            m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_MIDDLE]);
        m_vecImage.push_back(m_arrImage[(int)GROUND_IMAGE::IMAGE_RIGHT]);
        break;
    }

    m_Size.cx = m_arrImage[0]->GetSize().cx * 0.5f;      //사이즈 세팅
    m_Size.cy = m_arrImage[0]->GetSize().cy * 0.5f;

    m_Size.cx *= divide;
}