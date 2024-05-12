#pragma once
#include"UIPanel.h"
#ifndef UI_LABEL_H
#define UI_LABEL_H
namespace ENGINE
{
	class UILabel : public UIPanel
	{
	protected:
		std::string text;
		COLORREF color;
		HFONT font,oldFont;		//HFONT 글꼴속성
	public:
		UILabel() : color(0), font(NULL), oldFont(NULL) { uiType = UIType::LABEL;}
		void Initialize(const std::string& text, COLORREF color = RGB(0, 0, 0), HFONT font = NULL);//색 배경 폰트 글자 세팅

		void SetColor(COLORREF color) { this->color = color; }
		void SetText(const std::string& text);
		void SetFont(HFONT font);

		LPCSTR GetText() { return text.c_str(); }
		virtual void Draw() override;
	protected:
		virtual void SetRect(bool pivotCenter) override;
	};
}
#endif
