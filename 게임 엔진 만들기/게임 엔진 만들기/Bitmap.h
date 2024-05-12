#pragma once
#include "EngineMecro.h"

#ifndef BITMAP_H
#define BITMAP_H

namespace ENGINE
{
	enum Pivot { Centor = 1 << 0, Left = 1 << 1, Right = 1 <<2, Top = 1 << 3, Bottom = 1 << 4, };
	class Bitmap
	{
	private:
		HDC memDC;
		HDC alphaBlendDC;
		HBITMAP halphaBlendBitmap;
		HBITMAP hBitmap;
		SIZE origin, dest;
		RECT src;
		POINT pivot;
		INT pivotType;
		BLENDFUNCTION bf;
	public:
		~Bitmap();
		void Load(std::string name);	//��Ʈ�� �̹����� �ε��ϰ� �޸� DC�� �����
		void SetDrawSize(unsigned int width = 0U, unsigned int height = 0U);	//���� ȭ�鿡 ��µ� ũ�⸦ ����
		void ResetSize() { dest = origin; }		//ȭ�鿡 ��µǴ� ũ�⸦ ����ũ��� ����

		void SetAlphaValue(int alp) { bf.SourceConstantAlpha = alp;}		//alpha�� ����
		int GetAlphaValue() { return bf.SourceConstantAlpha; }		//alpha�� �޾ƿ���

		//Sprites �̹����� ������ ��ġ���� ������ ũ�⸸ŭ ���.
		void SliceSource(unsigned int cx, unsigned int cy, unsigned int width, unsigned int height)
		{
			src = { (long)cx,(long)cy,(long)width,(long)height };
		}
		void SetPivot(int pivot);
		void ResetPivot() { pivot = { 0,0 }; }

		bool Bitblt(int x, int y);		//�����״�� ȭ�鿡 ���
		bool StretchBlt(int x, int y);	//������ ��� ������� ������ ���
		// ������ ��� ������� �����ϰ� ���� ���� ����ó���Ͽ� ���.
		bool TransparentBlt(int x, int y, unsigned int transparent = RGB(255, 0, 255));
		bool AlphaBlend(int x, int y);

		SIZE GetBitmapSize()const { return origin; }//������Ʈ�� ũ�� %
		SIZE GetSize()const { return dest; }	//ȭ�鿡 ��µǴ� �̹���
	};
}
#endif
