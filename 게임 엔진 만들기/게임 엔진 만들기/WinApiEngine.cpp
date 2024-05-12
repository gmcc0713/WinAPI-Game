#include "WinApiEngine.h"
#include "InputManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

namespace ENGINE
{
	WinApiEngine::WinApiEngine(HINSTANCE hInstance, std::wstring title, INT32 per_x, INT32 per_y,
		UINT32 width, UINT32 height) : isInit(FALSE), title(title), x(0), y(0), width(width), height(height)
	{
		WNDCLASSEXW wcex =
		{
			sizeof(WNDCLASSEX),			// �� ����ü�� ũ��
			CS_HREDRAW | CS_VREDRAW,	//�������� ��� ����,(CS_HREDRAW | CS_VREDRAW) ������ �̵��̳� ũ�������� Ŭ���̾�Ʈ�� ���μ��ΰ� ����Ǹ� �ٽñ׸� 
			WndProc,					//������ �޼��� ó���� ����� ���ν���
			0,							//cbClsExtra : Ŭ������ ���� ���� �޸� �Ҵ�
			0,							//cbWndExtra : �����츦 ���� ���� �޸� �Ҵ�. �Ϲ������� ��� X
			hInstance,					//�ش� ���ø����̼��� �ν��Ͻ� �ڵ�
			0,0,0,						//������, Ŀ��, ������ ���� ����
			NULL,						//�޴��̸�, �޴��� ��뿩�θ� ����
			L"2DENGINEWindowClass",		//������ Ŭ���� �̸�. ������ ������ �̿�.
			NULL						//���� ������ ����.
		};
		RegisterClassExW(&wcex);

		HWND hWnd = CreateWindow(
			TEXT("2DEngineWindowClass"), title.c_str(),
			WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
			nullptr, nullptr, hInstance, nullptr);

		if (!hWnd) return;

		RECT rcWindow, rcClient;
		GetWindowRect(hWnd, &rcWindow);
		GetClientRect(hWnd, &rcClient);

		//CreateWindow�� ���ڷ� ���� �ʺ�, ���� ���� ����ũ �� ����� ũ�⸦ �����ϴ� ���̱� ������,
		//�� ���� ���� ���Ͽ� ������ ����� ���ϴ� Ŭ���̾�Ʈ �������� �ٽ� �����.
		UINT32 cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
		UINT32 cy = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);
		
		int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);	//SM_CXFULLSCREEN : ��üȭ���� �ʺ�
		int screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);	//SM_CYFULLSCREEN : ��üȭ���� ����
		per_x = clamp(per_x, 0, 100);// per_x�� per_y�� �� ������ 0~100���̷� ����
		per_y = clamp(per_y, 0, 100);

		x = per_x * 0.01f * (screenWidth - width); // �����츦 �����(Screen) ������ Ư�� ��ġ�� ����
		y = per_y * 0.01f * (screenHeight - height);

		MoveWindow(hWnd, x, y, width + cx, height + cy, false); //Window�� ��ġ �� ũ�⸦ �缳��
		
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
		srand((unsigned)time(NULL));
		
		//Scene Initialized
		SceneMgr->Initialize(hWnd, width, height);

		isInit = TRUE;
	}

	WinApiEngine::~WinApiEngine() { Release(); }

	INT WinApiEngine::Run()
	{
		if (!isInit) return -1;	//�ʱ�ȭ �Ǿ�����������

		MSG msg; ZeroMemory(&msg, sizeof(msg));
		while (WM_QUIT != msg.message)	//Game Loop
		{
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else { SceneMgr->Render(); }//�޼����� �߻����� �ʾ�����
		}
		Release();


		return (int)msg.wParam;
	}
	
	VOID WinApiEngine::Release()
	{
		SceneMgr->Destroy();
		/*Scene Destry*/
	}
}	//namespace ENGINE

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	ENGINE::InputMgr->InputProc(iMessage, wParam, lParam);
	switch (iMessage)
	{
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
	return 0;
}