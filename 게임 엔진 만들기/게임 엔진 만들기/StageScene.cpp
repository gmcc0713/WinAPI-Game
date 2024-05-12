#include "StageScene.h"
StageScene::StageScene()
{

}
void StageScene::Initialize()
{
    ResourceMgr->Load("background.bmp");
    ResourceMgr->Load("StageBG.bmp");
    ResourceMgr->Load("pause_normal.bmp");
    ResourceMgr->Load("pause_pressed.bmp");
    ResourceMgr->Load("base_panel.bmp");
    ResourceMgr->Load("continue_normal.bmp");
    ResourceMgr->Load("continue_pressed.bmp");
    ResourceMgr->Load("Menu_Normal.bmp");
    ResourceMgr->Load("Menu_Pressed.bmp");
    ResourceMgr->Load("Restart_Normal.bmp");
    ResourceMgr->Load("Restart_Pressed.bmp");
    ResourceMgr->Load("Door.bmp");
    ResourceMgr->Load("Ground_1.bmp");
    ResourceMgr->Load("Ground_2.bmp");
    ResourceMgr->Load("Ground_3.bmp");
    ResourceMgr->Load("Ground_4.bmp");
    ResourceMgr->Load("SmallGround_1.bmp");
    ResourceMgr->Load("SmallGround_2.bmp");
    ResourceMgr->Load("SmallGround_3.bmp");
    ResourceMgr->Load("SmallGround_4.bmp");
    ResourceMgr->Load("Life_1.bmp");
    ResourceMgr->Load("Life_2.bmp");
    ResourceMgr->Load("Box.bmp");
    ResourceMgr->Load("FireBall.bmp");
    ResourceMgr->Load("ClearStage.bmp");
    

    bounds = SceneMgr->GetWidth();

    background = ResourceMgr->GetBitmap("StageBG.bmp");
    background->SetDrawSize(bounds, SceneMgr->GetHeight());

    m_alphaBitmap = *ResourceMgr->GetBitmap("background.bmp");        //화면 alphablend를 위한 비트맵
    m_alphaBitmap.SetAlphaValue(0);
    m_alphaBitmap.SetDrawSize(bounds, SceneMgr->GetHeight());

    m_Player = new Player;
    m_Player->Initialize();
    m_PlayerTr = m_Player->GetTransform();
    m_PlayerSr = static_cast<SpriteRenderer*>(m_Player->GetComponent(ComponentType::Graphic));



    m_Life[(int)LIFE::LIFE_FULL] = ResourceMgr->GetBitmap("Life_1.bmp");
    m_Life[(int)LIFE::LIFE_EMPTY] = ResourceMgr->GetBitmap("Life_2.bmp");


    pauseBtn = UIMgr->AddUI<UIButton>("Pause Btn");
    pauseBtn->Initialize("pause_normal.bmp", "pause_pressed.bmp", "", "", DrawType::Transparent);
    pauseBtn->SetPosition(bounds - pauseBtn->GetSize().cx - 22, 10);
    pauseBtn->SetListener(std::bind(&StageScene::PauseBtnClickHandler, this));

    m_RestartBtn = UIMgr->AddUI<UIButton>("Restart Btn");
    m_RestartBtn->Initialize("Restart_Normal.bmp", "Restart_Pressed.bmp", "", "", DrawType::Transparent);
    m_RestartBtn->SetPosition(bounds - m_RestartBtn->GetSize().cx - 100, 10);
    m_RestartBtn->SetListener(std::bind(&StageScene::RestartBtnClickHandler, this));

    m_TimeLabel = UIMgr->AddUI<UILabel>("Time Label");
    m_TimeLabel->Initialize("Time : " + std::to_string(TimeMgr->GetGameTime()),RGB(255,255,255), SceneMgr->GetFont());
    m_TimeLabel->SetPosition(bounds*0.5f, 40,true);

    m_StageLabel = UIMgr->AddUI<UILabel>("Stage Label");
    m_StageLabel->Initialize(std::to_string((int)m_eStage)+ " Stage", RGB(255, 255, 255), SceneMgr->GetFont());
    m_StageLabel->SetPosition(bounds * 0.1f+10, 40, true);

    m_InputNameLabel = UIMgr->AddUI<UILabel>("Stage Label");
    m_InputNameLabel->Initialize( "", RGB(255, 255, 255), SceneMgr->GetFont());
    m_InputNameLabel->SetPosition(bounds * 0.5f, SceneMgr->GetHeight()*0.5f, true);

    GameClearWIndowSet();
    PauseButtonSet();

   
    bounds -= m_PlayerSr->GetDrawSize().cx;
    isPause = FALSE;
    m_eStage = STAGE::STAGE_1;
    SetObject();
    m_bIsStageEnd = false;
    m_eEndType = END_TYPE::NONE;
    m_bClearGame = false;
}
void StageScene::GameClearWIndowSet()
{
    m_GameClearWindow = UIMgr->AddUI<UIImage>("GameClear Canvas");
    if (m_GameClearWindow)
    {
        m_GameClearWindow->Initialize("ClearStage.bmp", DrawType::Transparent);
        m_GameClearWindow->SetPosition(bounds * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);


        UILabel* ClearLabel = UIMgr->AddUI<UILabel>("Clear Label", m_GameClearWindow);
        ClearLabel->Initialize("Game Clear", RGB(255, 255, 255), SceneMgr->GetFont());
        ClearLabel->SetPosition(m_GameClearWindow->GetSize().cx * 0.5f, 100, true);

        UILabel* InputNameLabel = UIMgr->AddUI<UILabel>("InputName Label", m_GameClearWindow);
        InputNameLabel->Initialize("↓ 이름 입력 ↓", RGB(255, 255, 255), SceneMgr->GetFont());
        InputNameLabel->SetPosition(m_GameClearWindow->GetSize().cx * 0.5f, m_GameClearWindow->GetSize().cy * 0.35f, true);
    }
}
void StageScene::PauseButtonSet()
{
    pauseWindow = UIMgr->AddUI<UIImage>("PauseWindow Canvas");
    if (pauseWindow)
    {
        pauseWindow->Initialize("base_panel.bmp", DrawType::Transparent);
        pauseWindow->SetPosition(bounds * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);

        UIButton* continueBtn = UIMgr->AddUI<UIButton>("Continue Btn", pauseWindow);
        continueBtn->Initialize("continue_normal.bmp", "continue_pressed.bmp", "", "", DrawType::Transparent);
        continueBtn->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f - 100, true);
        continueBtn->SetListener(std::bind(&StageScene::ContinueBtnClickHandler, this));

        UIButton* quitBtn = UIMgr->AddUI<UIButton>("Quit Btn", pauseWindow);
        quitBtn->Initialize("Menu_Normal.bmp", "Menu_Pressed.bmp", "", "", DrawType::Transparent);
        quitBtn->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f + 50, true);
        quitBtn->SetListener(std::bind(&StageScene::QuitBtnClickHandler, this));
        pauseWindow->SetEnable(FALSE);
    }
}
void StageScene::Release()
{
    REL_DEL(m_Player);
    ClearStage();
}

void StageScene::Update(const float& deltaTime)
{
    if (m_bClearGame)
    {
        m_GameClearWindow->Update();
        NameInput();
    }
    else if (m_bIsStageEnd)                               //스테이지가 종료되었는지
    {
        EndAnimation();                            //스테이지 전환 애니메이션 재생
    }
    else
    {
        if (isPause)                            //정지 버튼이눌러졌는가
        {
            pauseWindow->Update();
        }
        if (isPause) return;


        for (auto iter = m_vecMonster.begin(); iter != m_vecMonster.end();)
        {
            if ((*iter)->Update(deltaTime))
            {
                REL_DEL((*iter));
                iter = m_vecMonster.erase(iter);

            }
            else
            {
                iter++;
            }
        }

        if (m_Player->Update(deltaTime))
        {
            m_eEndType = END_TYPE::NEWGAME;
            m_bIsStageEnd = true;
        }

        for (Object* ob : m_vecObject)
        {
            ob->Update(deltaTime);
        }
        for (Ground* ground : m_vecGround)
        {
            ground->Update(deltaTime);
        }


        if (0 > m_PlayerTr->position.x) m_PlayerTr->position.x = 0;
        if (bounds < m_PlayerTr->position.x) m_PlayerTr->position.x = bounds;


        for (auto iter = m_vecItem.begin(); iter != m_vecItem.end();)
        {
            if ((*iter)->Update(deltaTime))
            {
                iter = m_vecItem.erase(iter);
            }
            else
            {
                iter++;
            }
        }

        pauseBtn->Update();
        m_RestartBtn->Update();

        m_TimeLabel->SetText("Time : " + std::to_string(TimeMgr->GetGameTime()));
        m_TimeLabel->Update();

        m_StageLabel->SetText(std::to_string((int)m_eStage+1) + " Stage");
        m_StageLabel->Update();

        CollideCheck();
    }
   
}

void StageScene::Draw()
{
    background->StretchBlt(0, 0);
    if (m_bClearGame)
    {
        m_GameClearWindow->Draw();
        m_InputNameLabel->Draw();
        return;
    }

    for (Object* ob : m_vecObject)
        ob->Draw();

    for (Ground* ground : m_vecGround)
        ground->Draw();

    for (Item* item : m_vecItem)
        item->Draw();

    m_Player->Draw();

    for (Monster* monster: m_vecMonster)
        monster->Draw();


    pauseBtn->Draw();
    m_RestartBtn->Draw();
    m_TimeLabel->Draw();
    m_StageLabel->Draw();

    if (isPause)
    {
        pauseWindow->Draw();
    }

    PlayerLifeDraw();

    m_alphaBitmap.AlphaBlend(0, 0);
}

void StageScene::PlayerLifeDraw()
{
    int playerLife = m_Player->GetLife();
    for (int i = 0; i < 3; i++)
    {
        if (i < playerLife)
            m_Life[(int)LIFE::LIFE_FULL]->TransparentBlt(50*i,SceneMgr->GetHeight() - m_Life[0]->GetBitmapSize().cy);
        else
            m_Life[(int)LIFE::LIFE_EMPTY]->TransparentBlt(50 * i, SceneMgr->GetHeight() - m_Life[0]->GetBitmapSize().cy);
    }
}

void StageScene::CollideCheck()
{
    ItemCollideCheck();
    MonsterCollideCheck();
    ObjectCollideCheck();
    GroundCollideCheck();
}

void StageScene::MonsterCollideCheck()      //몬스터의 충돌 확인
{
    std::vector<RECT> BombRect;

    for (Item* item : m_vecItem)
    {
        if (item->GetItemName() == ITEM_NAME::BOMB && item->GetIsEffectSet())           //터진 폭탄 아이템의 충돌 사각형 모두 저장
        {
            BombRect.push_back(item->GetRect());
        }
    }

    for (auto iter = m_vecMonster.begin(); iter != m_vecMonster.end(); iter++)      //몬스터들의 각각 충돌검사
    {
        (*iter)->PlayerCollideCheck(m_Player);
        for (RECT rect : BombRect)
        {
            (*iter)->CollideCheck(rect);                    //폭탄아이템과 충돌시
        }
    }
}

void StageScene::ItemCollideCheck()
{
    for (auto iter = m_vecItem.begin();iter != m_vecItem.end();iter++)
    {
        (*iter)->CollideCheck(m_Player);
    }
}

void StageScene::ObjectCollideCheck()
{
    for (Object* ob : m_vecObject)
    {
        if (ob->CollideCheck(m_Player->GetRect(), m_Player))
        {
            m_eEndType = END_TYPE::NEXTSTAGE;
            m_bIsStageEnd = true;
        }
    }
}

void StageScene::GroundCollideCheck()
{
    for (Ground* ground : m_vecGround)
    {
        m_Player->GroundCollideDirectionCheck(ground->GetRect());

        for (Monster* monster : m_vecMonster)
            monster->GroundCollideDirectionCheck(ground->GetRect());
        ground->CollideCheck(m_Player);
    }

}

void StageScene::PauseBtnClickHandler()
{
    isPause = TRUE;
    pauseBtn->SetInteracterble(FALSE);
    pauseWindow->SetEnable(TRUE);
}

void StageScene::ContinueBtnClickHandler()
{
    pauseWindow->SetEnable(FALSE);
    pauseBtn->SetInteracterble(TRUE);
    isPause = FALSE;
}

void StageScene::RestartBtnClickHandler()
{
    RestartGame();
}

void StageScene::QuitBtnClickHandler()
{
    ENGINE::SceneMgr->LoadScene("StartScene");
}

void StageScene::RestartGame()
{
    ClearStage();
    SetObject();
}

void StageScene::ClearObject()
{
    for (Ground* ground : m_vecGround)
        REL_DEL(ground);
    m_vecGround.clear();

    for (Monster* monster : m_vecMonster)
        REL_DEL(monster);
    m_vecMonster.clear();

    for (Object* object : m_vecObject)
        REL_DEL(object);
    m_vecObject.clear();

    for (Item* item : m_vecItem)
        REL_DEL(item);
    m_vecItem.clear();

}
void StageScene::ClearStage()
{
    ClearObject();
    if(m_Player)
        m_Player->Reset();
    m_alphaBitmap.SetAlphaValue(0);
    m_bIsStageEnd = false;
}
void StageScene::SetObject()
{
    switch (m_eStage)
    {
        case STAGE::STAGE_1:
        {
            Ground* ground = new Ground;
            ground->Initialize(0, 600, 8);
            m_vecGround.push_back(ground);

            Item* key = new Key;
            key->Initialize(400, 500);
            m_vecItem.push_back(key);

            Door* door = new Door;
            door->Initialize(600, 500);
            m_vecObject.push_back(door);

            break;
        }
        case STAGE::STAGE_2:
        {
            Ground* ground = new Ground;
            ground->Initialize(0, 600, 2);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(300, 600, 2);
            m_vecGround.push_back(ground);
            ground = new Ground;
            ground->Initialize(600, 600, 2);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(0, 300, 8);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(0, 70, 8);
            m_vecGround.push_back(ground);


            Monster* monster = new MonsterSnake;
            monster->Initialize(0, 200, 800, 200);
            m_vecMonster.push_back(monster);

            Potal* potal = new Potal;
            potal->Initialize(700, 500, 700, 200);
            m_vecObject.push_back(potal);

            Door* door = new Door;
            door->Initialize(0, 200);
            m_vecObject.push_back(door);

            WoodTrap* woodTrap = new WoodTrap(TRAP_DIRECTION::DOWN);
            woodTrap->Initialize(100, 120);
            m_vecObject.push_back(woodTrap);

           woodTrap = new WoodTrap(TRAP_DIRECTION::DOWN);
            woodTrap->Initialize(300, 120);
            m_vecObject.push_back(woodTrap);


            Item* bomb = new BombObject;
            bomb->Initialize(500, 200);
            m_vecItem.push_back(bomb);

            Item* key = new Key;
            key->Initialize(600, 200);
            m_vecItem.push_back(key);

            break;
        }
        case STAGE::STAGE_3:
        {
            Ground* ground = new Ground;
            ground->Initialize(0, 600, 2);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(270, 470, 1,GROUND_SIZE::SIZE_SMALL);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(120, 400, 1, GROUND_SIZE::SIZE_SMALL);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(400, 400, 1, GROUND_SIZE::SIZE_SMALL);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(100, 250, 1, GROUND_SIZE::SIZE_SMALL);
            m_vecGround.push_back(ground);

            for (int i = 0; i < 4; i++)
            {
                ground = new Ground;
                ground->Initialize(250+150*i, 320, 1, GROUND_SIZE::SIZE_SMALL);
                m_vecGround.push_back(ground);
            }
            ground = new Ground;
            ground->Initialize(0, 250, 1);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(500, 600, 1);
            m_vecGround.push_back(ground);

            ground = new Ground;
            ground->Initialize(700, 600, 1);
            m_vecGround.push_back(ground);

            WoodTrap* woodTrap = new WoodTrap(TRAP_DIRECTION::UP);
            woodTrap->Initialize(255, 270);
            m_vecObject.push_back(woodTrap);

            woodTrap = new WoodTrap(TRAP_DIRECTION::UP);
            woodTrap->Initialize(555, 270);
            m_vecObject.push_back(woodTrap);


            Potal* potal = new Potal;
            potal->Initialize(500, 500, 680, 270);
            m_vecObject.push_back(potal);

            Door* door = new Door;
            door->Initialize(0, 150);
            m_vecObject.push_back(door);


            Item* key = new Key;
            key->Initialize(700, 500);
            m_vecItem.push_back(key);

            break;
        }
    }
}
void StageScene::EndAnimation()
{
        int alphaValue = m_alphaBitmap.GetAlphaValue();
        alphaValue += 3;

        if (alphaValue > 255)
        {
            ClearStage();
            SetStage();

            return;
        }
        m_alphaBitmap.SetAlphaValue(alphaValue);
}
void StageScene::SetStage()
{
    
    switch (m_eEndType)
    {
    case END_TYPE::NEWGAME:                         //게임 처음부터시작
        m_eStage = STAGE::STAGE_1;                  //생명력 3주기
        m_Player->SetLife(3);                       //플레이어 라이프 3으로 초기화
        TimeMgr->SetGameTime(0);                    //게임 시간 0초로 초기화
        break;
    case END_TYPE::NEXTSTAGE:
        if (m_eStage < STAGE::STAGE_3)
        {
            m_eStage = STAGE((int)m_eStage + 1);
        }
        else
        {
            m_Player->SetTime(TimeMgr->GetGameTime());
            m_bClearGame = true;
        }
        break;
        
    }
    m_eEndType = END_TYPE::NONE;

    SetObject();
}
void StageScene::NameInput()
{
    std::string name = m_Player->GetName();
    int len = name.length();
    if (InputMgr->GetKeyDown(VK_RETURN)&& name.length() >0)
    {

        PlayerInfo player{ name ,m_Player->GetLife(),m_Player->GetTime() };        //플레이어 정보 저장
        RankMgr->RegistePlayerNewRank(player);                                          //정보등록
        
        SceneMgr->LoadScene("RankScene");                                               //rank scene load

        return;
    }
    else if (InputMgr->GetKeyDown(VK_BACK))
    {
        if (len != 0)
        {
            name[len - 1] = 0;
            name.pop_back();
        }
    }

    std::string input = InputMgr->GetChar();
    if (input >= "A" || input <= "Z")            //영어 입력시
    {
        
         if (len < 5&& input!="\b")
         {
             name += input;
         }
    }

    m_Player->SetName(name);
    m_InputNameLabel->SetText(name);
}
StageScene::~StageScene()
{
    Release();
}
