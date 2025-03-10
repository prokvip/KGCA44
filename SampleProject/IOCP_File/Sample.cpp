#include "Sample.h"
#include <iostream>
#define _DEBUG_LOAD

#define NUM_READ_SIZE (4096*4096)

template<typename ... Args>
std::string format_string(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
	std::unique_ptr<char[]> buffer(new char[size]);
	snprintf(buffer.get(), size, format.c_str(), args ...);
	return std::string(buffer.get(), buffer.get() + size - 1);
}
void   Sample::FileInformation(HANDLE hFile)
{
	DWORD iSector_Clustor = 0;
	DWORD iByte_Sector = 0;
	DWORD iFree_Clustor = 0;
	DWORD iTotal_Clustor = 0;
	GetDiskFreeSpace(L"C:\\",&iSector_Clustor,&iByte_Sector,&iFree_Clustor,	&iTotal_Clustor);

	ULARGE_INTEGER avail, total, free;
	avail.QuadPart = 0L;
	total.QuadPart = 0L;
	free.QuadPart = 0L;
	GetDiskFreeSpaceEx(TEXT("C:\\"), &avail, &total, &free);
	UINT m_avail, m_total, m_free;
	m_total = (int)(total.QuadPart >> 30);
	m_free = (int)(free.QuadPart >> 30);
	std::string msg = format_string("C: Total Size: %d GB , Free Size : %d GB\n", m_total, m_free);

	BY_HANDLE_FILE_INFORMATION info;
	GetFileInformationByHandle(hFile, &info);
}
//VOID WINAPI COMPLETION_ROUTINE_Load(
//	_In_    DWORD dwErrorCode,
//	_In_    DWORD dwNumberOfBytesTransfered,
//	_Inout_ LPOVERLAPPED lpOverlapped)
//{
//	Sample* pSample = (Sample*)lpOverlapped->hEvent;
//	if (pSample)
//	{
//		CloseHandle(pSample->m_hLoadFile);
//		pSample->m_DxWrite.Add(L"�ε� �ϼ�");
//		pSample->m_bLoadFinish = true;
//		pSample->AsyncCopy(L"copy.zip");
//	}
//}
//VOID WINAPI COMPLETION_ROUTINE_Write(
//	_In_    DWORD dwErrorCode,
//	_In_    DWORD dwNumberOfBytesTransfered,
//	_Inout_ LPOVERLAPPED lpOverlapped)
//{
//	Sample* pSample = (Sample*)lpOverlapped->hEvent;
//	if (pSample)
//	{
//		delete[] pSample->m_pFileBuffer;
//		CloseHandle(pSample->m_hCopyFile);
//		pSample->m_DxWrite.Add(L"���� �ϼ�");
//	}
//}

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
				CloseHandle(pSample->m_hLoadFile);
				pSample->m_DxWrite.Add(L"�ε� �ϼ�");
				pSample->m_bLoadFinish = true;

				DWORD dwWrite;
				WriteFile(pSample->m_hCopyFile, 
						  pSample->m_pFileBuffer,
						  pSample->m_FileSize.LowPart,
						  &dwWrite,
						  &pSample->m_CopyOV );
			}
			if (CompletionKey == 2000)
			{
				CloseHandle(pSample->m_hCopyFile);
				pSample->m_DxWrite.Add(L"���� �ϼ�");
				pSample->m_bWriteFinish = true;
				break;
			}
		}
		else
		{
			if (GetLastError() == WAIT_TIMEOUT)
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
		m_pFileBuffer = new TCHAR[m_FileSize.LowPart];
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

		// ���ν����� �񵿱� ����� �۾� ����
		BOOL bRet = ReadFile(m_hLoadFile,
			m_pFileBuffer, dwLength,
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