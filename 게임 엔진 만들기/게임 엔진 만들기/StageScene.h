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

	std::vector<Ground*> m_vecGround;				//땅, 움직일수있는 땅
	std::vector<Monster*> m_vecMonster;				//몬스터
	std::vector<Item*> m_vecItem;					// 폭탄, 열쇠
	std::vector<Object*> m_vecObject;				// 문, 순간이동 장치
	

	void PauseBtnClickHandler();			//정지버튼
	void RestartBtnClickHandler();			//재시작 버튼
	void ContinueBtnClickHandler();			//계속하기 버튼
	void QuitBtnClickHandler();				//나가기 버튼

	void GameClearWIndowSet();
	void PauseButtonSet();

	void CollideCheck();			//스테이지속 오브젝트충돌체크
	void ItemCollideCheck();		//아이템 충돌 체크
	void MonsterCollideCheck();		//몬스터의 충돌 체크
	void ObjectCollideCheck();
	void GroundCollideCheck();


	void RestartGame();
	void PlayerLifeDraw();		//플레이어의 라이프 받아와서 그리기

	void ClearObject();			//스테이지 자체 클리어
	void ClearStage();			//스테이지 속 오브젝트 지우기
	void SetObject();			//오브젝트 설치
	void SetStage();			//스테이지 설치

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

