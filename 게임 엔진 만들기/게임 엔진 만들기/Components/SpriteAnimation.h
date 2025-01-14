#include "../Component.h"

#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

namespace ENGINE
{
	class SpriteAnimation : public AnimationComponent
	{
	private:
		INT frame;
		FLOAT animTimer;
		Component* renderer;
		bool m_IsChange;
	private:
		SpriteAnimation();
	public:
		SpriteAnimation(UINT divX = 1, UINT divY = 1, BOOL autoPlay = FALSE);

		// AnimationComponent을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override;
		bool GetIsChange() { return m_IsChange; }
	};
}

#endif // !SPRITE_ANIMATION_H