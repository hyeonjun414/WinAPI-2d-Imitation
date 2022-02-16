// WinAPI2dImitation.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI2dImitation.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 실행된 프로세스의 시작 주소
    _In_opt_ HINSTANCE hPrevInstance, // 이전에 실행된 인스턴스 값
    _In_ LPWSTR    lpCmdLine, // 명령으로 입력된 프로그램의 인수
    _In_ int       nCmdShow) // 프로그램이 시작될 형태
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    // 리소스 뷰의 String Table에서 ID값으로 String을 가져오는 함수
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // 프로그램 타이틀을 불러옴.
    LoadStringW(hInstance, IDC_WINAPI2DIMITATION, szWindowClass, MAX_LOADSTRING); // 프로그램 클래스를 불러옴.

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 초기화
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 정보를 불러온다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2DIMITATION));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 단축키에 해당하는 메세지인지 확인
        //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        //{
        TranslateMessage(&msg);     // 기본 메시지를 번역
        DispatchMessage(&msg);      // 메시지가 온 대로 처리 -> WndProc 실행
    //}
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우 창의 정보를 저장하기 위한 구조체
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); // 구조체의 크기 설정

    wcex.style = CS_HREDRAW | CS_VREDRAW;           // 윈도우 클래스의 스타일 지정
    wcex.lpfnWndProc = WndProc;                     // 윈도우의 메세지를 처리하는 함수 WndProc 지정
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;                     // 인스턴스 핸들러 지정
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WINAPI2DIMITATION));      // 아이콘 지정
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);                      // 커서 지정
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);                    // 바탕화면 지정
    wcex.lpszMenuName = nullptr;                                        // 메뉴 옵션 지정
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 스몰 아이콘 지정

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // 프로그램에 대한 주소값
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 윈도우 창에 대한 주소값
    HWND hWnd = CreateWindowW(szWindowClass,         // 클래스 이름
        szTitle,               // 윈도우 이름
        WINSTYLE,              // 윈도우 스타일
        WINSTARTX,             // 윈도우 시작 X
        WINSTARTY,             // 윈도우 시작 Y
        WINSIZEX,              // 윈도우 가로 크기
        WINSIZEY,              // 윈도우 세로 크기
        nullptr,               // 부모 윈도우
        nullptr,               // 메뉴 핸들
        hInstance,             // 프로세스 인스턴스의 핸들
        nullptr);              // 추가 매개변수

    if (!hWnd)
    {
        return FALSE;
    }

    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = WINSIZEX;
    rc.bottom = WINSIZEY;
    // 실제 내용 창이 크기에 맞게끔 하도록 사이즈.
    AdjustWindowRect(&rc, WINSTYLE, false);
    // 위에서 얻은 사이즈로 윈도우 사이즈를 세팅하자.
    SetWindowPos(hWnd, NULL, WINSTARTX, WINSTARTY,
        (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

POINT g_mousePos = { 0,0 };
POINT g_mouseStartPos = { 0,0 };
POINT g_mouseEndPos = { 0,0 };
POINT g_keyPos = { 0, 0 };
bool isClick = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
    case WM_LBUTTONDOWN:
        //// 클릭한 위치에 원을 출력하는 기능 -> 클릭된 좌표를 가져옴
        //g_mousePos.x = LOWORD(lParam);
        //g_mousePos.y = HIWORD(lParam);
        //InvalidateRect(hWnd, NULL, false); // 화면을 다시 그리는 함수
        isClick = true;
        g_mouseStartPos.x = LOWORD(lParam);
        g_mouseStartPos.y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        isClick = false;
        break;
    case WM_MOUSEMOVE:
        // 클릭한 위치에 원을 출력하는 기능 -> 클릭된 좌표를 가져옴
        g_mouseEndPos.x = LOWORD(lParam);
        g_mouseEndPos.y = HIWORD(lParam);
        g_mousePos.x = LOWORD(lParam);
        g_mousePos.y = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, false); // 화면을 다시 그리는 함수
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
            // 기타 다른 키들은 VK로 등록되어 있다 ex. VK_UP ...
        case VK_LEFT:
        case 'A':
            g_keyPos.x -= 10;
            break;
        case VK_RIGHT:
        case 'D':
            g_keyPos.x += 10;
            break;
        case VK_UP:
        case 'W':
            g_keyPos.y -= 10;
            break;
        case VK_DOWN:
        case 'S':
            g_keyPos.y += 10;
            break;
        default:
            break;
        }
        InvalidateRect(hWnd, NULL, false); // 화면을 다시 그리는 함수
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        if (isClick)
            Rectangle(hdc, g_mouseStartPos.x, g_mouseStartPos.y, g_mouseEndPos.x, g_mouseEndPos.y);

        //if(g_mousePos.x != 0 && g_mousePos.y != 0)
        //    Ellipse(hdc, g_mousePos.x - 50, g_mousePos.y - 50, g_mousePos.x + 50, g_mousePos.y + 50);
        if (g_keyPos.x != 0 && g_keyPos.y != 0)
            Rectangle(hdc, g_keyPos.x - 100, g_keyPos.y - 100, g_keyPos.x + 100, g_keyPos.y + 100);
        EndPaint(hWnd, &ps);
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