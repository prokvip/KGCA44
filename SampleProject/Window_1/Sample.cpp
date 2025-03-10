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
    //hInstance = �ü������ �߱޵� ���α׷��� ��ȣ�� ���̼���(�㰡��)
     
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX); // �Ű����� ��������
    wcex.style = CS_HREDRAW | CS_VREDRAW; // ������⹰
    wcex.lpfnWndProc = WndProc;  // ��ȭ��ȣ,�ּ�,����
    wcex.hInstance = hInstance;  // �㰡��
    wcex.lpszClassName = L"KGCA";// �����
    //wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    //wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(128,128,128));
    // �ü������ �̷� �����츦 ����Ұž�. (�ü������ �Ű��Ѵ�.���)
    WORD hr = RegisterClassExW(&wcex);

    // �����ϰ� �ϰ��ϰ� ���ȴ�.
     //hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    // �������ڵ�(HWND) �������, ����
    HWND hWnd = CreateWindowW(
        L"KGCA", L"���������α׷�1", 
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
    // �����찡 �����Ǹ� �ټ��� �޼����� �ش� �����쿡 ���۵ȴ�.
    // ��� ���۵� �޼����� �޼���ť�� ����ȴ�.
    // �Ϻ��� �޼����� �޼���ť�� ������� �ʰ� 
    // ���� ���������ν���(WndProc)�� ȣ���Ѵ�.
    
    // ����� �޼��� ť���� 1���� �޼����� �����ͼ� ó���ϴ�.   
    // �޼���ť�� �޼����� ���� �� ���� ó���Ѵ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
       TranslateMessage(&msg); // Ű�� �����Ѵ�.
       DispatchMessage(&msg);  // ���ν����� �����Ѵ�.       
    }
    //MessageBox(NULL, L"�ȳ��ϼ���", L"�޼����ڽ�", MB_OK);
}