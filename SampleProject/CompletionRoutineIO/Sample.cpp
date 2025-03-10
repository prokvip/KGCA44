#include "Sample.h"

#define _DEBUG_LOAD

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
VOID WINAPI COMPLETION_ROUTINE_Load(
	_In_    DWORD dwErrorCode,
	_In_    DWORD dwNumberOfBytesTransfered,
	_Inout_ LPOVERLAPPED lpOverlapped)
{
	Sample* pSample = (Sample*)lpOverlapped->hEvent;
	if (pSample)
	{
		CloseHandle(pSample->m_hLoadFile);
		pSample->m_DxWrite.Add(L"로드 완성");
		pSample->m_bLoadFinish = true;
		pSample->AsyncCopy(L"copy.zip");
	}
}
VOID WINAPI COMPLETION_ROUTINE_Write(
	_In_    DWORD dwErrorCode,
	_In_    DWORD dwNumberOfBytesTransfered,
	_Inout_ LPOVERLAPPED lpOverlapped)
{
	Sample* pSample = (Sample*)lpOverlapped->hEvent;
	if (pSample)
	{
		delete[] pSample->m_pFileBuffer;
		CloseHandle(pSample->m_hCopyFile);
		pSample->m_DxWrite.Add(L"복사 완성");
	}
}

void   Sample::AsyncLoad(const TCHAR* filename)
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
		FileInformation(m_hLoadFile);

		GetFileSizeEx(m_hLoadFile, &m_FileSize);
		m_pFileBuffer = new TCHAR[m_FileSize.LowPart];
		DWORD dwLength = m_FileSize.LowPart;
		m_loadOV.hEvent = (HANDLE)this;
		BOOL bRet = ReadFileEx(m_hLoadFile,
			m_pFileBuffer, dwLength,
			&m_loadOV, COMPLETION_ROUTINE_Load);
		if (bRet == FALSE)
		{
			m_DxWrite.Add(L"로드 에러!");
		}
	}

}
void   Sample::AsyncCopy(const TCHAR* filename)
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
		DWORD dwLength = m_FileSize.LowPart;
		m_CopyOV.hEvent = (HANDLE)this;
		BOOL bRet = WriteFileEx(m_hCopyFile, m_pFileBuffer,
			m_FileSize.LowPart,
			 &m_CopyOV, COMPLETION_ROUTINE_Write);
		if (bRet == FALSE)
		{
			m_DxWrite.Add(L"로드 에러!");
		}
	}
}
void   Sample::Init()
{
	//동기입출력(read,write:recv,send)
	//FileWrite(L"test.txt");
	//FileRead(L"test.txt");
	//Load(L"bigdata.zip");
	//Copy(L"datacopy.zip");
	AsyncLoad(L"data.zip");
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