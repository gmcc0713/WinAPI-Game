#include "UILabel.h"
#include "SceneManager.h"
namespace ENGINE
{
	void UILabel::SetRect(bool pivotCenter)
	{
		///////
		if (font) oldFont = (HFONT)SelectObject(SceneMgr->GetBackDC(), font);	//backDC의  GDI핸들값 font로 교체 이전의 font oldfont에 저장
		GetTextExtentPoint32A(SceneMgr->GetBackDC(), text.c_str(), text.length(), & size);//지덩된 텍스트 문자열의 너비와 높이를 계산
		if (font) SelectObject(SceneMgr->GetBackDC(),oldFont);		//backDC의  GDI핸들값 oldFont로 교체 이전에 font oldfont에 저장
		POINT pos = position;
		if (pivotCenter)
		{
			pos.x -= size.cx * 0.5f;
			pos.y -= size.cy * 0.5f;
		}
		rect = { pos.x,pos.y,pos.x + size.cx,pos.y + size.cy };
	}

	void UILabel::Initialize(const std::string& text, COLORREF color, HFONT font)	//색 배경 폰트 글자 세팅
	{
		SetBkMode(SceneMgr->GetBackDC(), TRANSPARENT);
		SetColor(color);
		SetFont(font);
		SetText(text);
	}
	void UILabel::SetText(const std::string& text)
	{
		this->text = text;
		SetRect(pivotCenter);
	}
	void UILabel::SetFont(HFONT font)
	{
		if (font)
		{
			this->font = font;
			if (!text.empty()) SetRect(pivotCenter);
		}
	}
	void UILabel::Draw()
	{
		if (!isEnable)	return;
		if (font)	oldFont = (HFONT)SelectObject(SceneMgr->GetBackDC(), font);	// backDC의 GDI핸들값 font로 변경후 oldfont에 넣기 
		SetTextColor(SceneMgr->GetBackDC(), color);		//색지정
		DrawTextA(SceneMgr->GetBackDC(), text.c_str(), text.length(), &rect, NULL);	//글자출력
		if (font) SelectObject(SceneMgr->GetBackDC(), oldFont);
		UIPanel::Draw();
	}
}