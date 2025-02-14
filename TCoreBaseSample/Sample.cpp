#include "Sample.h"

HANDLE hThread1;
HANDLE hThread2;
int g_iData = 0;

// 유저모드의 동기화 객체 : 임계영역을 설정한다.
CRITICAL_SECTION g_CriticalSection;


DWORD WINAPI ThreadWorkProc1(LPVOID param)
{
	TDxWrite* pWrite = (TDxWrite*)param;
	for (int i = 0; i < 10; i++)
	{
		std::wstring data = L"ThreadWorkProc1:";
		
		// 임계영역 설정
		EnterCriticalSection(&g_CriticalSection);
		{
			g_iData = 1;
			data += std::to_wstring(g_iData);
			pWrite->Add(data);

			Sleep(1);

			data += std::to_wstring(g_iData);
			pWrite->Add(data);
		}
		LeaveCriticalSection(&g_CriticalSection);
	}
	return 0;
}
DWORD WINAPI ThreadWorkProc2(LPVOID param)
{
	TDxWrite* pWrite = (TDxWrite*)param;
	for (int i = 0; i < 10; i++)
	{
		std::wstring data = L"ThreadWorkProc2:";
		EnterCriticalSection(&g_CriticalSection);
		{
			g_iData = 2;
			data += std::to_wstring(g_iData);
			pWrite->Add(data);

			Sleep(1);

			data += std::to_wstring(g_iData);
			pWrite->Add(data);
		}
		LeaveCriticalSection(&g_CriticalSection);
	}
	return 0;
}
void   Sample::Init()
{
	InitializeCriticalSection(&g_CriticalSection);

	DWORD dwThreadID;
	hThread1 = CreateThread(NULL, 0, 
		ThreadWorkProc1, &m_DxWrite, 0, &dwThreadID);
	hThread2 = CreateThread(NULL, 0,
		ThreadWorkProc2, &m_DxWrite, 0, &dwThreadID);
}
void   Sample::Frame()
{
};
void   Sample::Render()
{
	D2D1_RECT_F rt = { 0.0f, 350.0f, 800.0f, 600.0f };
	m_DxWrite.DirectDraw(rt, L"TSceneGameIn::Render");
}
void   Sample::Release()
{
	DeleteCriticalSection(&g_CriticalSection);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
}

//GameStart(800, 600);
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	Sample sample;
	sample.SetWindowClass(hInstance);
	sample.SetWindow(L"test", 800, 600);
	sample.GameRun();
}