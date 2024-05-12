#include "UILabel.h"
#include "SceneManager.h"
namespace ENGINE
{
	void UILabel::SetRect(bool pivotCenter)
	{
		///////
		if (font) oldFont = (HFONT)SelectObject(SceneMgr->GetBackDC(), font);	//backDC��  GDI�ڵ鰪 font�� ��ü ������ font oldfont�� ����
		GetTextExtentPoint32A(SceneMgr->GetBackDC(), text.c_str(), text.length(), & size);//������ �ؽ�Ʈ ���ڿ��� �ʺ�� ���̸� ���
		if (font) SelectObject(SceneMgr->GetBackDC(),oldFont);		//backDC��  GDI�ڵ鰪 oldFont�� ��ü ������ font oldfont�� ����
		POINT pos = position;
		if (pivotCenter)
		{
			pos.x -= size.cx * 0.5f;
			pos.y -= size.cy * 0.5f;
		}
		rect = { pos.x,pos.y,pos.x + size.cx,pos.y + size.cy };
	}

	void UILabel::Initialize(const std::string& text, COLORREF color, HFONT font)	//�� ��� ��Ʈ ���� ����
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
		if (font)	oldFont = (HFONT)SelectObject(SceneMgr->GetBackDC(), font);	// backDC�� GDI�ڵ鰪 font�� ������ oldfont�� �ֱ� 
		SetTextColor(SceneMgr->GetBackDC(), color);		//������
		DrawTextA(SceneMgr->GetBackDC(), text.c_str(), text.length(), &rect, NULL);	//�������
		if (font) SelectObject(SceneMgr->GetBackDC(), oldFont);
		UIPanel::Draw();
	}
}