#include "PCH.h"
#include "framework.h"
#include "HollowKnight Silksong.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
HWND    hWnd;
INT    FrameIntervalTimeA, FrameIntervalTimeB;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);       // Detect Memory Leak

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOLLOWKNIGHTSILKSONG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) { return FALSE; }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOLLOWKNIGHTSILKSONG));

    MSG msg;
    msg.message= WM_NULL;

    GameManager GM;
    GM.Initialize();

    DWORD dwTime = GetTickCount();
    FrameIntervalTimeA = 10;
    FrameIntervalTimeB = 0;
    while (true)    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            if (dwTime + FrameIntervalTimeA + FrameIntervalTimeB < GetTickCount())
            {
                GM.Update();
                GM.LateUpdate();
                GM.Render();

                dwTime = GetTickCount();
            }
        }
    }
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_MAINCURSOR));
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(NULL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MAINICON));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   //SetProcessDPIAware();

   RECT WindowScale = { 0, 0, DEFAULT_WINDOW_CX, DEFAULT_WINDOW_CY };
   AdjustWindowRect(&WindowScale, WS_OVERLAPPEDWINDOW, FALSE);

   int WindowResolutionX = GetSystemMetrics(SM_CXSCREEN);
   int WindowResolutionY = GetSystemMetrics(SM_CYSCREEN);

   // 창 화면 중앙 위치 계산
   int WindowPositionX = WindowResolutionX / 2 - DEFAULT_WINDOW_CX / 2;
   int WindowPositionY = WindowResolutionY / 2 - DEFAULT_WINDOW_CY / 2;

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       WindowPositionX, WindowPositionY, DEFAULT_WINDOW_CX, DEFAULT_WINDOW_CY, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) { return FALSE; }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;
        }break;
    case WM_COMMAND:
        {
           int wmId = LOWORD(wParam);
           // 메뉴 선택을 구문 분석합니다:
           switch (wmId)
           {
           case IDM_ABOUT:
               DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
               break;
           case IDM_EXIT:
               DestroyWindow(hWnd);
               break;
           default:
               return DefWindowProc(hWnd, message, wParam, lParam);
           }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
