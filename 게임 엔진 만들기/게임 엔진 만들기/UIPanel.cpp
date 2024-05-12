#include "UIPanel.h"
namespace ENGINE
{
	UIPanel::UIPanel() :
		isEnable(true), pivotCenter(false),
		position({ 0, 0 }), localPosition({ 0, 0 }),
		rect({ 0,0,0,0 }), size({ 0,0 }),
		parent(nullptr) {uiType = UIType::PANEL;}

	UIPanel::~UIPanel() { child.clear(); }

	void UIPanel::SetLocalPos(int x, int y)	//부모 위치로부터 자기위치 세팅
	{
		position = localPosition = { x,y };		//화면상 위치와 부모와의 위치 세팅	
		if (parent) position = { x + parent->rect.left,y + parent->rect.top };	//부모가 있을때  (부모의 화면상 위치 + 부모와의 위치) -> 자기 화면상위치
		SetRect(pivotCenter);
		for (UIPanel* ui : child)ui->RefreshPos();		//변경된 자기 위치로 자식들 위치 세팅
	}
	void UIPanel::SetPosition(int x, int y, bool pivotCenter)
	{
		this->pivotCenter = pivotCenter;
		if (parent) SetLocalPos(x - parent->rect.left, y - parent->rect.top);	//부모가있으면 자기위치-부모위치
		else SetLocalPos(x, y);		//부모가 없으면 자기위치
	}
	void UIPanel::SetLocalPosition(int x, int y, bool pivotCenter)
	{
		this->pivotCenter = pivotCenter;
		SetLocalPos(x,y);
	}
	void UIPanel::Update()
	{
		if (!isEnable) return;
		for (UIPanel* ui : child)ui->Update();	//자식들 Update
	}

	void UIPanel::Draw()
	{
		if (!isEnable) return;	

		for (UIPanel* ui : child)ui->Draw();		//isEnable이 true일때 자식들 그리기
	}

	UIPanel* UIPanel::AddChildUI(UIPanel* ui)
	{
		if (!ui) return nullptr;

		child.push_back(ui);		//ui를 자식으로 추가
		ui->SetParent(this);		//자식으로 추가한 ui의 부모를 자기자신으로 세팅

		std::sort(child.begin(), child.end());		//인접한 중복원소 삭제를 위한 정렬
		child.erase(std::unique(child.begin(), child.end()), child.end());		//unique 함수 저장되어있는 원소들중 인접한 중복된 값을 삭제,
																				//삭제되고 남은 기존의 자리에는 원래 원소들이 들어간다,erase(닫힌구간,끝)
		return ui;
	}
	void UIPanel::RemoveChildUI(UIPanel* ui)
	{
		if (!ui)return;

		std::vector<UIPanel*>::iterator iter = std::find(child.begin(), child.end(), ui);	//ui를 child에 있는지 찾기,없으면 end반환
		if (child.end() != iter)
		{
			child.erase(iter);	//자식위치에서 삭제, 메모리 해제 x
			(*iter)->SetParent(nullptr);	//해당 자식의 부모 비우기
		}
	}
	void UIPanel::RefreshPos()
	{
		SetLocalPos(localPosition.x, localPosition.y);	//자신의 부모와의 위치로 자식들 위치세팅
	}

	UIPanel* UIPanel::GetChild(int index)
	{
		if (0 > index || child.size() <= index) return nullptr;	//index가 음수이거나 자식의 수가 작을때
		return child[index];
	}

}
