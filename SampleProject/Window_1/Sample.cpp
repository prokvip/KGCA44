#include <windows.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
     case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return  DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI wWinMain(
     HINSTANCE hInstance,
     HINSTANCE hPrevInstance,
     LPWSTR    lpCmdLine,
     int       nCmdShow)
{
    //hInstance = 운영체제에서 발급된 프로그램의 번호된 라이센스(허가권)
     
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX); // 신고서류의 페이지수
    wcex.style = CS_HREDRAW | CS_VREDRAW; // 지상건출물
    wcex.lpfnWndProc = WndProc;  // 전화번호,주소,메일
    wcex.hInstance = hInstance;  // 허가권
    wcex.lpszClassName = L"KGCA";// 건축명
    //wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    //wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(128,128,128));
    // 운영체제에게 이런 윈도우를 사용할거야. (운영체제에세 신고한다.등록)
    WORD hr = RegisterClassExW(&wcex);

    // 건축하고 완공하고 살면된다.
     //hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 윈도우핸들(HWND) 건축대장, 증축
    HWND hWnd = CreateWindowW(
        L"KGCA", L"윈도우프로그램1", 
        WS_OVERLAPPED ,
        100, 100, 800, 600, 
        nullptr, nullptr, 
        hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);   

    MSG msg;
    // 윈도우가 생성되면 다수의 메세지가 해당 윈도우에 전송된다.
    // 모두 전송된 메세지는 메세지큐에 저장된다.
    // 일부의 메세지는 메세지큐에 저장되지 않고 
    // 직접 윈도우프로시져(WndProc)를 호출한다.
    
    // 저장된 메세지 큐에서 1개씩 메세지를 가져와서 처리하다.   
    // 메세지큐에 메세지가 없을 때 까지 처리한다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
       TranslateMessage(&msg); // 키를 번역한다.
       DispatchMessage(&msg);  // 프로시져로 전송한다.       
    }
    //MessageBox(NULL, L"안녕하세여", L"메세지박스", MB_OK);
}