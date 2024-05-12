#include "SpriteAnimation.h"
#include "SpriteRenderer.h"
#include "../TimeManager.h"

namespace ENGINE
{
	SpriteAnimation::SpriteAnimation(UINT divX, UINT divY, BOOL autoPlay) : 
		AnimationComponent(divY, divX, autoPlay),
		frame(0), animTimer(frameRate), renderer(nullptr)
	{ }

	VOID SpriteAnimation::Operate(GameObject* Owner)
	{
		renderer = Owner->GetComponent(ComponentType::Graphic);			//�׷����� renderer�� �ִ´�
		if (!renderer) return;

		static_cast<SpriteRenderer*>(renderer)->SetSrc(frame, index);	// Ÿ��ĳ��Ʈ ������/static_cast<�ٲٷ��� �ϴ� Ÿ��>(���)/�������� ��ȯ ������ Ÿ���� ��ȯ
		m_IsChange = false;

		if (!isPlaying)			//�������� �ƴҶ�
		{
			frame = 0;
			animTimer = frameRate;
			return;
		}

		animTimer += TimeMgr->DeltaTime() * speed;	//�ҿ�� �ð� * �ӵ�
		if (frameRate <= animTimer)
		{
			animTimer -= frameRate;
			frame += (isReverse ? -1 : 1); //isIeverse ���̸� -1,false�� 1 ���Ѵ� 
			frame = Repeat(frame, (int)(length - 1));
			m_IsChange = true;
		}
	}
	VOID SpriteAnimation::Reset()
	{
		index = 0U;
		speed = 1U;
		frame = 0;
		animTimer = frameRate;
	}
}