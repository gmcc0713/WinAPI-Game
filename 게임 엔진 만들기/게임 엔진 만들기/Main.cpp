#include "WinApiEngine.h"
#include "StageScene.h"
#include "StartScene.h"
#include "HelpScene.h"
#include "RankScene.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPWSTR IpCmdLine,
						_In_ int nCmdShow)
{
	ENGINE::WinApiEngine engine(hInstance, TEXT("WinAPI 2D Engine"),
		ENGINE::Client_Per_X, ENGINE::Client_Per_Y,
		ENGINE::ClientSize_Width, ENGINE::ClientSize_Height);

	//TODO : 여기에 새로운 씬 등록 및 로드
	ENGINE::SceneMgr->RegisterScene("StartScene", new StartScene);
	ENGINE::SceneMgr->RegisterScene("StageScene", new StageScene);
	ENGINE::SceneMgr->RegisterScene("RankScene", new RankScene);
	ENGINE::SceneMgr->RegisterScene("HelpScene", new HelpScene);

	ENGINE::SceneMgr->LoadScene("StartScene");
	engine.Run();
	return 0;
	
}