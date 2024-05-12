#pragma once
#include"UIPanel.h"
#include "SceneManager.h"
#include "Bitmap.h"
#ifndef UI_IMAGE_H
#define UI_IMAGE_H
namespace ENGINE
{
	enum class DrawType {Normal,Transparent};
	class UIImage : public UIPanel
	{
	protected:
		Bitmap* image;
		DrawType type;
	public:
		UIImage() :image(nullptr), type(DrawType::Normal) { uiType = UIType::IMAGE; }
		void Initialize(const std::string& imageName, DrawType type = DrawType::Normal);
		virtual void Draw() override;		//투명화 or일반 그리기
		void SetChangSize(float sizePersent);
	protected:
		virtual void SetRect(bool pivotCenter) override;	//해당 이미지의 크기와 위치로 rect세팅
	};
}
#endif
