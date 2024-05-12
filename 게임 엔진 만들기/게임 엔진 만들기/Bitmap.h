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
		void Load(std::string name);	//비트맵 이미지를 로드하고 메모리 DC를 만든다
		void SetDrawSize(unsigned int width = 0U, unsigned int height = 0U);	//실제 화면에 출력될 크기를 변경
		void ResetSize() { dest = origin; }		//화면에 출력되는 크기를 원본크기로 변경

		void SetAlphaValue(int alp) { bf.SourceConstantAlpha = alp;}		//alpha값 지정
		int GetAlphaValue() { return bf.SourceConstantAlpha; }		//alpha값 받아오기

		//Sprites 이미지의 임의의 위치부터 임의의 크기만큼 출력.
		void SliceSource(unsigned int cx, unsigned int cy, unsigned int width, unsigned int height)
		{
			src = { (long)cx,(long)cy,(long)width,(long)height };
		}
		void SetPivot(int pivot);
		void ResetPivot() { pivot = { 0,0 }; }

		bool Bitblt(int x, int y);		//원본그대로 화면에 출력
		bool StretchBlt(int x, int y);	//설정한 출력 사이즈로 변경후 출력
		// 설정한 출력 사이즈로 변경하고 지정 색을 투명처리하여 출력.
		bool TransparentBlt(int x, int y, unsigned int transparent = RGB(255, 0, 255));
		bool AlphaBlend(int x, int y);

		SIZE GetBitmapSize()const { return origin; }//원본비트맵 크기 %
		SIZE GetSize()const { return dest; }	//화면에 출력되는 이미지
	};
}
#endif
