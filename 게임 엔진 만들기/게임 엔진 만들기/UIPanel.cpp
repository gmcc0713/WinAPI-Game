#include "UIPanel.h"
namespace ENGINE
{
	UIPanel::UIPanel() :
		isEnable(true), pivotCenter(false),
		position({ 0, 0 }), localPosition({ 0, 0 }),
		rect({ 0,0,0,0 }), size({ 0,0 }),
		parent(nullptr) {uiType = UIType::PANEL;}

	UIPanel::~UIPanel() { child.clear(); }

	void UIPanel::SetLocalPos(int x, int y)	//�θ� ��ġ�κ��� �ڱ���ġ ����
	{
		position = localPosition = { x,y };		//ȭ��� ��ġ�� �θ���� ��ġ ����	
		if (parent) position = { x + parent->rect.left,y + parent->rect.top };	//�θ� ������  (�θ��� ȭ��� ��ġ + �θ���� ��ġ) -> �ڱ� ȭ�����ġ
		SetRect(pivotCenter);
		for (UIPanel* ui : child)ui->RefreshPos();		//����� �ڱ� ��ġ�� �ڽĵ� ��ġ ����
	}
	void UIPanel::SetPosition(int x, int y, bool pivotCenter)
	{
		this->pivotCenter = pivotCenter;
		if (parent) SetLocalPos(x - parent->rect.left, y - parent->rect.top);	//�θ������� �ڱ���ġ-�θ���ġ
		else SetLocalPos(x, y);		//�θ� ������ �ڱ���ġ
	}
	void UIPanel::SetLocalPosition(int x, int y, bool pivotCenter)
	{
		this->pivotCenter = pivotCenter;
		SetLocalPos(x,y);
	}
	void UIPanel::Update()
	{
		if (!isEnable) return;
		for (UIPanel* ui : child)ui->Update();	//�ڽĵ� Update
	}

	void UIPanel::Draw()
	{
		if (!isEnable) return;	

		for (UIPanel* ui : child)ui->Draw();		//isEnable�� true�϶� �ڽĵ� �׸���
	}

	UIPanel* UIPanel::AddChildUI(UIPanel* ui)
	{
		if (!ui) return nullptr;

		child.push_back(ui);		//ui�� �ڽ����� �߰�
		ui->SetParent(this);		//�ڽ����� �߰��� ui�� �θ� �ڱ��ڽ����� ����

		std::sort(child.begin(), child.end());		//������ �ߺ����� ������ ���� ����
		child.erase(std::unique(child.begin(), child.end()), child.end());		//unique �Լ� ����Ǿ��ִ� ���ҵ��� ������ �ߺ��� ���� ����,
																				//�����ǰ� ���� ������ �ڸ����� ���� ���ҵ��� ����,erase(��������,��)
		return ui;
	}
	void UIPanel::RemoveChildUI(UIPanel* ui)
	{
		if (!ui)return;

		std::vector<UIPanel*>::iterator iter = std::find(child.begin(), child.end(), ui);	//ui�� child�� �ִ��� ã��,������ end��ȯ
		if (child.end() != iter)
		{
			child.erase(iter);	//�ڽ���ġ���� ����, �޸� ���� x
			(*iter)->SetParent(nullptr);	//�ش� �ڽ��� �θ� ����
		}
	}
	void UIPanel::RefreshPos()
	{
		SetLocalPos(localPosition.x, localPosition.y);	//�ڽ��� �θ���� ��ġ�� �ڽĵ� ��ġ����
	}

	UIPanel* UIPanel::GetChild(int index)
	{
		if (0 > index || child.size() <= index) return nullptr;	//index�� �����̰ų� �ڽ��� ���� ������
		return child[index];
	}

}
