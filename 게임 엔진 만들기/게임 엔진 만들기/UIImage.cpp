#include "UIImage.h"
#include "ResourceManager.h"
namespace ENGINE
{
	void UIImage::SetRect(bool pivotCenter)
	{
		POINT pos = position;
		size = image->GetBitmapSize();
		if (pivotCenter)
		{
			pos.x -= size.cx * 0.5f;
			pos.y -= size.cy * 0.5f;
		}
		rect = { pos.x,pos.y,pos.x + size.cx,pos.y + size.cy };
	}
	void UIImage::Initialize(const std::string& imageName, DrawType type)
	{
		image = ResourceMgr->GetBitmap(imageName);
		this->type = type;
		SetRect(pivotCenter);
	}
	void UIImage::Draw()
	{
		if (!isEnable)return;

		if (image)
		{
			switch (type)	
			{
			case DrawType::Transparent:	image->TransparentBlt(rect.left, rect.top); break;	//투명화로 그리기
			default: image->Bitblt(rect.left, rect.top); break;								//그냥그리기
			}
		}
		UIPanel::Draw();
	}
	void UIImage::SetChangSize(float sizePersent)
	{
		size.cx *= sizePersent;
		size.cy *= sizePersent;
		if (pivotCenter)
		{
			position.x -= size.cx * 0.5f;
			position.y -= size.cy * 0.5f;
		}
		rect = { position.x,position.y,position.x + size.cx,position.y + size.cy };
		image->SetDrawSize(size.cx, size.cy);
	}
}