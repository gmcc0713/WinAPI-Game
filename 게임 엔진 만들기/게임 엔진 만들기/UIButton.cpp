#include "UIButton.h"
#include "ResourceManager.h"
#include "InputManager.h"
namespace ENGINE
{
	UIButton::UIButton():clickListner(nullptr),pressedListener(nullptr),
						 state(ButtonState::NONE), isUp(false), isInteractable(true),
						 normal(nullptr),pressed(nullptr),hover(nullptr),disable(nullptr)
						{uiType = UIType::BUTTON;}

	void UIButton::Initialize(const std::string& normal, const std::string& pressed, const std::string& hover, const std::string& disable, DrawType  type)
	{
		UIImage::Initialize(normal, type);//drawtype,image,rect 세팅

		this->disable = this->hover = this->pressed = this->normal = image;
		if (!pressed.empty()) this->pressed = ResourceMgr->GetBitmap(pressed);
		if (!hover.empty()) this->hover = ResourceMgr->GetBitmap(hover);
		if (!disable.empty()) this->disable = ResourceMgr->GetBitmap(disable);
	}

	void UIButton::SetListener(EventListener click, EventListener pressed)
	{
		clickListner = click;
		pressedListener = pressed;
	}
	void UIButton::Update()
	{
		if (!isEnable) return;

		UIImage::Update();	//pannel 자식객체들 Update

		if (!isInteractable)
		{
			state = ButtonState::NONE;
			if (disable) image = disable;
			return;
		}
		isUp = InputMgr->GetMouseButtonUp(VK_LBUTTON);	//mouse버튼이 올라왔는지
		if (PtInRect(&rect, InputMgr->GetMousePosition()))	//마우스 위치와 충돌검사
		{
			switch (state)
			{
			case ButtonState::NONE:	state = ButtonState::HOVER;			//버튼상태가 none일때 hover로
			case ButtonState::HOVER: 
				if (InputMgr->GetMouseButtonDown(VK_LBUTTON)) 
					state = ButtonState::PRESSED; break;//버튼을 눌렀을때 그 키가 keys에 없으면 버튼상태 pressed로 
			case ButtonState::PRESSED: if (isUp && clickListner) clickListner(); break;		
			}
		}
		else if (ButtonState::PRESSED != state) state = ButtonState::NONE;	//충돌하지 않았고 버튼이 pressed가 아닐때 state = none

		switch (state)
		{
		case ButtonState::NONE:	image = normal; break;
		case ButtonState::HOVER: image = hover; break;
		case ButtonState::PRESSED: image = pressed; if (isUp)state = ButtonState::NONE; if (pressedListener)pressedListener(); break;
		}
	}
	void UIButton::SetChangeSize(float sizePersent)
	{
		UIImage::SetChangSize(sizePersent);
		normal->SetDrawSize(size.cx, size.cy);
		hover->SetDrawSize(size.cx, size.cy);
		pressed->SetDrawSize(size.cx, size.cy);

	}
}
