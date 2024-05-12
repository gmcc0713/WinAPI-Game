#pragma once
#include"UIImage.h"
#ifndef UI_BUTTON_H
#define UI_BUTTON_H
namespace ENGINE
{
	class UIButton : public UIImage
	{
		enum class ButtonState {NONE,HOVER,PRESSED};
	protected:
		EventListener clickListner, pressedListener;
		ButtonState state;
		bool isUp, isInteractable;
		Bitmap* normal, * pressed, * hover, * disable;
	public:
		UIButton();

		void Initialize(const std::string& normal, const std::string& pressed = "", const std::string& hover = "",const std::string& disable = "", DrawType  type = DrawType::Normal);
		void SetListener(EventListener click, EventListener pressed = nullptr);
		void SetInteracterble(bool interactable) { isInteractable = interactable; }
		bool IsInteracterble() const { return isInteractable; }
		virtual void Update()override;
		void SetChangeSize(float sizePersent);
	};
}
#endif // !UI_BUTTON_H

