#include "TWindow.h"
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
// 윈도우클래스 등록
bool   TWindow::SetWindowClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX); // 신고서류의 페이지수
    wcex.style = CS_HREDRAW | CS_VREDRAW; // 지상건출물
    wcex.lpfnWndProc = WndProc;  // 전화번호,주소,메일
    wcex.hInstance = m_hInstance;  // 허가권
    wcex.lpszClassName = L"KGCA";// 건축명
    //wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    //wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
    // 운영체제에게 이런 윈도우를 사용할거야. (운영체제에세 신고한다.등록)
    WORD hr = RegisterClassExW(&wcex);
	return true;
}
// 윈도우창 생성
bool   TWindow::SetWindow(
    std::wstring title,
    UINT iWindowX, UINT iWindowY)
{
    HWND hWnd = CreateWindowW(
        L"KGCA", title.c_str(),
        WS_OVERLAPPEDWINDOW,//WS_OVERLAPPED,
        0, 0, iWindowX, iWindowY,
        nullptr, nullptr,
        m_hInstance, nullptr);
    if (!hWnd)
    {
        return false;
    }
    ShowWindow(hWnd, SW_SHOW);
    m_hWnd = hWnd;
	return true;
}
// 메세지 프로시쳐, 처리
bool   TWindow::MessageProcess()
{
    MSG msg;   
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            m_bRun = false;
            return false;
        };
        TranslateMessage(&msg); // 키를 번역한다.
        DispatchMessage(&msg);  // 프로시져로 전송한다.
        return true;
    }
    return false;
}

//// 메세지 프로시쳐, 처리
//bool   TWindow::MessageProcess() 
//{
//    MSG msg;
//    std::clock_t tick = std::clock();
//    std::clock_t start = std::clock();
//    std::clock_t end = std::clock();
//    double gametime = 0.0;
//    double time = 0.0f;
//    double secondPerFrame = 0.0f;
//    UINT iFrame = 0;
//    while (m_bRun)
//    {
//        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//        {
//            TranslateMessage(&msg); // 키를 번역한다.
//            DispatchMessage(&msg);  // 프로시져로 전송한다.
//        }
//        else
//        {
//            
//            end = std::clock();
//            std::clock_t t1 = end - tick; // 1000단위
//            
//            secondPerFrame = (end - start) / (double)CLOCKS_PER_SEC;
//            gametime += secondPerFrame;
//            time += secondPerFrame;
//            if (time > 1.0)
//            {
//                std::wstring msgTime = std::to_wstring(gametime);
//                msgTime += L" ";
//                msgTime += std::to_wstring(secondPerFrame);
//                msgTime += L" ";
//                msgTime += std::to_wstring(iFrame);
//                msgTime += L"\n";
//                OutputDebugString(msgTime.c_str());
//                time -= 1.0;
//                iFrame = 0;
//            }
//            
//            /*if (t1 >= 10)
//            {*/
//                iFrame++;
//                // 게임로직
//                GameRun();       
//              /*  tick = end;
//            }*/
//            start = end;
//        }
//    }
//	return true;
//}

