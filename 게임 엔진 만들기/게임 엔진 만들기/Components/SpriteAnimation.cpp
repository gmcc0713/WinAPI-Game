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
		renderer = Owner->GetComponent(ComponentType::Graphic);			//그래픽을 renderer에 넣는다
		if (!renderer) return;

		static_cast<SpriteRenderer*>(renderer)->SetSrc(frame, index);	// 타입캐스트 연산자/static_cast<바꾸려고 하는 타입>(대상)/논리적으로 변환 가능한 타입을 변환
		m_IsChange = false;

		if (!isPlaying)			//실행중이 아닐때
		{
			frame = 0;
			animTimer = frameRate;
			return;
		}

		animTimer += TimeMgr->DeltaTime() * speed;	//소요된 시간 * 속도
		if (frameRate <= animTimer)
		{
			animTimer -= frameRate;
			frame += (isReverse ? -1 : 1); //isIeverse 참이면 -1,false면 1 더한다 
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