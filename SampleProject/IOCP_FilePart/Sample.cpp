#include "Sample.h"
#include <iostream>
#define _DEBUG_LOAD

#define NUM_READ_SIZE (4096*2048)
// NUM_READ_SIZE 100  350byte
// read file 100byte
//   [0]~100, [100]~ 200, [200]~300, [300] ~ 350, 
// while file [0]~100,100~ 200, 200~300, 300 ~ 350, 
LARGE_INTEGER g_LargeRead;
LARGE_INTEGER g_LargeWrite;


bool DispatchRead(DWORD dwTrans, OVERLAPPED* ov, Sample* pSample)
{
	g_LargeRead.QuadPart += dwTrans;
	ZeroMemory(&pSample->m_CopyOV, sizeof(OVERLAPPED));
	pSample->m_CopyOV.Offset = g_LargeWrite.LowPart;
	pSample->m_CopyOV.OffsetHigh = g_LargeWrite.HighPart;

	DWORD dwWrite;
	BOOL bRet = WriteFile(pSample->m_hCopyFile,
		pSample->m_pFileBuffer,
		dwTrans,
		&dwWrite,
		&pSample->m_CopyOV);
	if (bRet == FALSE)
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_IO_PENDING)
		{
			return false;
		}
	}

	// �ϼ�
	if (pSample->m_FileSize.QuadPart == g_LargeRead.QuadPart)
	{
		return false;
	}
	return true;
}
bool DispatchWrite(DWORD dwTrans, OVERLAPPED* ov, Sample* pSample)
{
	g_LargeWrite.QuadPart += dwTrans;

	// �ϼ�
	if (pSample->m_FileSize.QuadPart == g_LargeWrite.QuadPart)
	{
		return false;
	}

	ZeroMemory(&pSample->m_loadOV, sizeof(OVERLAPPED));
	pSample->m_loadOV.Offset = g_LargeRead.LowPart;
	pSample->m_loadOV.OffsetHigh = g_LargeRead.HighPart;

	DWORD dwRead;
	BOOL bRet = ReadFile(pSample->m_hLoadFile,
		pSample->m_pFileBuffer,
		NUM_READ_SIZE,		
		&dwRead,
		&pSample->m_loadOV);
	if (bRet == FALSE)
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_IO_PENDING)
		{
			return false;
		}
	}
	return true;
}

DWORD WINAPI ThreadWorkerProc(LPVOID lpParameter)
{
	Sample* pSample = (Sample*)lpParameter;
	HANDLE hIOCP = pSample->m_hIOCP;
	while (pSample->m_bWriteFinish==false)
	{
		DWORD dwTransfer;
		ULONG_PTR CompletionKey;
		OVERLAPPED* Overlapped;
		// ��)�񵿱� �۾��� ����� IOCPť�� ����ȴ�.
		// ť�� ����� �񵿱� �۾��� ����� GetQueuedCompletionStatus�� �����´�.
		BOOL bRet = ::GetQueuedCompletionStatus(hIOCP, 
								&dwTransfer,
								&CompletionKey,
								&Overlapped, 1000);
		if (bRet == TRUE)
		{
			if (CompletionKey == 1000)
			{				
				if (!DispatchRead(dwTransfer, Overlapped, pSample))
				{
					CloseHandle(pSample->m_hLoadFile);
					pSample->m_bLoadFinish = true;
					pSample->m_DxWrite.Add(L"�ε� �ϼ�");
				}
			}
			if (CompletionKey == 2000)
			{
				if (!DispatchWrite(dwTransfer, Overlapped, pSample))
				{
					CloseHandle(pSample->m_hCopyFile);
					pSample->m_DxWrite.Add(L"���� �ϼ�");
					pSample->m_bWriteFinish = true;
					delete[] pSample->m_pFileBuffer;
					break;
				}
			}
		}
		else
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_HANDLE_EOF)
			{
				INT K = 0;
			}
			if (dwError == WAIT_TIMEOUT)
			{
				if (pSample->m_bWriteFinish == false)
				{
					pSample->m_DxWrite.Add(L"�۾� ��...");
				}
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
bool   Sample::CreateLoadFile(const TCHAR* filename)
{
	ZeroMemory(&m_loadOV, sizeof(OVERLAPPED));
	m_hLoadFile =
		CreateFile(filename, GENERIC_READ,
			0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED
#ifdef _DEBUG_LOAD
			| FILE_FLAG_SEQUENTIAL_SCAN
#endif
			, NULL);
	if (m_hLoadFile != INVALID_HANDLE_VALUE)
	{
		GetFileSizeEx(m_hLoadFile, &m_FileSize);
		m_pFileBuffer = new TCHAR[NUM_READ_SIZE];
		return true;
	}
	return false;
}
bool   Sample::CreateSaveFile(const TCHAR* filename)
{
	ZeroMemory(&m_CopyOV, sizeof(OVERLAPPED));
	m_hCopyFile =
		CreateFile(filename, GENERIC_WRITE,
			0, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED
#ifdef _DEBUG_LOAD
			| FILE_FLAG_WRITE_THROUGH
#endif
			, NULL);
	if (m_hCopyFile != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	return false;
}

void   Sample::Init()
{
	// ������ �뷮�� ��(100->10)���� �����ؼ� �ε� �� ����
	if (CreateLoadFile(L"../../data.zip") &&
		CreateSaveFile(L"save.zip"))
	{
		// IOCP ���ε�
		m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0,0,0);
		ULONG LoadCompletionKey = 1000;
		ULONG CopyCompletionKey = 2000;
		::CreateIoCompletionPort(m_hLoadFile, m_hIOCP, LoadCompletionKey, 0);
		::CreateIoCompletionPort(m_hCopyFile, m_hIOCP, CopyCompletionKey, 0);
		
		// ��) �񵿱� ������� �ݵ�� �۾��� ��Ų �����忡���� Ȯ�� �����ϴ�.
		// �� ������ �Ϸ� ���θ� ������ �����忡�� Ȯ���Ѵ�.
		// ��)IOCP�� ������ �����忡�� ������� Ȯ���� �����ϴ�.

		// �񵿱� �۾��� ����� Ȯ���ϴ� ������ ����.
		for (int iThread = 0; iThread < MAX_NUM_WORK_THREAD; iThread++)
		{
			DWORD threadID;
			m_hWorkerThread[iThread] = CreateThread(0,0,
				ThreadWorkerProc, this, 0, &threadID);
		}

		DWORD dwReadByte = 0;
		DWORD dwLength = m_FileSize.LowPart;

		g_LargeRead.QuadPart = 0;
		g_LargeWrite.QuadPart = 0;

		m_loadOV.Offset = g_LargeRead.LowPart;
		m_loadOV.OffsetHigh = g_LargeRead.HighPart;
		// ���ν����� �񵿱� ����� �۾� ����
		BOOL bRet = ReadFile(m_hLoadFile,
			m_pFileBuffer, NUM_READ_SIZE,
			&dwReadByte,
			&m_loadOV);
	}	
}
void   Sample::Frame()
{	
	SleepEx(0, TRUE);
};
void   Sample::Render()
{
	D2D1_RECT_F rt = { 0.0f, 350.0f, 800.0f, 600.0f };
	m_DxWrite.DirectDraw(rt, L"TSceneGameIn::Render");
}
void   Sample::Release()
{
	CloseHandle(m_hIOCP);
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