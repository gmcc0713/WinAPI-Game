#include "Bitmap.h"
#include "SceneManager.h"
namespace ENGINE
{
	Bitmap::~Bitmap()
	{
		DeleteDC(memDC);
		DeleteObject(hBitmap);
	}

	void Bitmap::Load(std::string name)
	{
		memDC = CreateCompatibleDC(SceneMgr->GetBackDC());
		hBitmap = (HBITMAP)LoadImageA(NULL, name.c_str(),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);//비트맵 이미지 로드
		SelectObject(memDC, hBitmap);

		BITMAP BitMap;
		GetObject(hBitmap, sizeof(BITMAP), &BitMap); //비트맵 정보얻기
		origin.cx = BitMap.bmWidth;
		origin.cy = BitMap.bmHeight;
		dest = origin; src = { 0,0,origin.cx,origin.cy };	//화면에 그려줄 크기와 rec를 원본크기로 지정

		pivot = { 0,0 };
		pivotType = (Pivot::Left | Pivot::Top);
		
		ZeroMemory(&bf, sizeof(bf));
		bf.SourceConstantAlpha = 255;

	
	}
	void Bitmap::SetDrawSize(unsigned int width, unsigned int height) 
	{
		dest = { (LONG)width,(LONG)height };
		SetPivot(pivotType); 
	}
	void Bitmap::SetPivot(int pivot)
	{
		pivotType = pivot;

		int halfWidth = dest.cx * 0.5f;
		int halfHeight = dest.cy * 0.5f;
		this->pivot = { -halfWidth,-halfHeight };

		if (pivot & Pivot::Left) this->pivot.x += halfWidth;
		if (pivot & Pivot::Right) this->pivot.x += -halfWidth;
		if (pivot & Pivot::Top) this->pivot.y += halfHeight;
		if (pivot & Pivot::Bottom) this->pivot.y += -halfHeight;
	}
	bool Bitmap::Bitblt(int x, int y)
	{
		return ::BitBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, src.right, src.bottom, memDC, src.left, src.top, SRCCOPY);
	}
	bool Bitmap::StretchBlt(int x, int y)
	{
		return ::StretchBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y,dest.cx,dest.cy, memDC, src.left, src.top, src.right, src.bottom, SRCCOPY);
	}
	bool Bitmap::TransparentBlt(int x, int y,unsigned int transparent)
	{
		return ::TransparentBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom, transparent);
	}
	bool Bitmap::AlphaBlend(int x, int y)
	{
		return ::AlphaBlend(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom, bf);
	}
}