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
		UIImage::Initialize(normal, type);//drawtype,image,rect ����

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

		UIImage::Update();	//pannel �ڽİ�ü�� Update

		if (!isInteractable)
		{
			state = ButtonState::NONE;
			if (disable) image = disable;
			return;
		}
		isUp = InputMgr->GetMouseButtonUp(VK_LBUTTON);	//mouse��ư�� �ö�Դ���
		if (PtInRect(&rect, InputMgr->GetMousePosition()))	//���콺 ��ġ�� �浹�˻�
		{
			switch (state)
			{
			case ButtonState::NONE:	state = ButtonState::HOVER;			//��ư���°� none�϶� hover��
			case ButtonState::HOVER: 
				if (InputMgr->GetMouseButtonDown(VK_LBUTTON)) 
					state = ButtonState::PRESSED; break;//��ư�� �������� �� Ű�� keys�� ������ ��ư���� pressed�� 
			case ButtonState::PRESSED: if (isUp && clickListner) clickListner(); break;		
			}
		}
		else if (ButtonState::PRESSED != state) state = ButtonState::NONE;	//�浹���� �ʾҰ� ��ư�� pressed�� �ƴҶ� state = none

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
