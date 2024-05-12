#pragma once
#include "EngineMecro.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "Player.h"
#include "Ground.h"
#include "BombObject.h"
#include "Key.h"
#include "Door.h"
#include "Monster.h"
#include "Potal.h"
#include "WoodTrap.h"
#include "Box.h"
#include "FireBall.h"
#include "MonsterBat.h"
#include "MonsterSnake.h"
#include "RankManager.h"
#include <algorithm>
#include <vector>
#include <string>
#define MAP_WIDTH_COUNT 8

struct MapElement { int x; int y; int index; };

enum class STAGE {STAGE_1 = 0, STAGE_2, STAGE_3,COUNT};
enum class LIFE { LIFE_FULL = 0, LIFE_EMPTY,LIFE_COUNT};
enum class END_TYPE {NEWGAME,NEXTSTAGE, NONE};

using namespace ENGINE;

class StageScene : public Scene
{
protected:
	bool isPause;
	Bitmap* background = nullptr;
	Bitmap m_alphaBitmap;
	UIButton* pauseBtn;
	UIButton* m_RestartBtn;

	UILabel* m_TimeLabel;
	UILabel* m_StageLabel;
	UILabel* m_InputNameLabel;

	UIImage* pauseWindow;
	UIImage* m_GameClearWindow;

	bool m_bIsStageEnd;
	bool m_bClearGame;

	Bitmap* m_Life[(int)LIFE::LIFE_COUNT];
	int bounds;
	STAGE m_eStage;
	END_TYPE m_eEndType;


	Player* m_Player;
	std::string m_name;
	
	Transform* m_PlayerTr = nullptr;
	SpriteRenderer* m_PlayerSr = nullptr;

	std::vector<Ground*> m_vecGround;				//��, �����ϼ��ִ� ��
	std::vector<Monster*> m_vecMonster;				//����
	std::vector<Item*> m_vecItem;					// ��ź, ����
	std::vector<Object*> m_vecObject;				// ��, �����̵� ��ġ
	

	void PauseBtnClickHandler();			//������ư
	void RestartBtnClickHandler();			//����� ��ư
	void ContinueBtnClickHandler();			//����ϱ� ��ư
	void QuitBtnClickHandler();				//������ ��ư

	void GameClearWIndowSet();
	void PauseButtonSet();

	void CollideCheck();			//���������� ������Ʈ�浹üũ
	void ItemCollideCheck();		//������ �浹 üũ
	void MonsterCollideCheck();		//������ �浹 üũ
	void ObjectCollideCheck();
	void GroundCollideCheck();


	void RestartGame();
	void PlayerLifeDraw();		//�÷��̾��� ������ �޾ƿͼ� �׸���

	void ClearObject();			//�������� ��ü Ŭ����
	void ClearStage();			//�������� �� ������Ʈ �����
	void SetObject();			//������Ʈ ��ġ
	void SetStage();			//�������� ��ġ

	void EndAnimation();
	void NameInput();
public:
	StageScene();
	~StageScene();
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update(const float& deltaTime) override;
	virtual void Draw()override;

};

