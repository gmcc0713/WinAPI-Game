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
		virtual void Draw() override;		//����ȭ or�Ϲ� �׸���
		void SetChangSize(float sizePersent);
	protected:
		virtual void SetRect(bool pivotCenter) override;	//�ش� �̹����� ũ��� ��ġ�� rect����
	};
}
#endif
