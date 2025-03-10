#pragma once
#include "TGameCore.h"
#define MAX_NUM_WORK_THREAD 2
// IOCP(Input,Output, Completion, Port)
class Sample : public TGameCore
{
public:
	TCHAR* m_pFileBuffer = nullptr;
	LARGE_INTEGER		m_FileSize;
public:
	virtual void   Init() override;
	virtual void   Frame() override;
	virtual void   Render() override;
	virtual void   Release() override;
public:
	bool   CreateLoadFile(const TCHAR* filename);
	bool   CreateSaveFile(const TCHAR* filename);
public:
	HANDLE m_hWorkerThread[MAX_NUM_WORK_THREAD];
	HANDLE m_hIOCP;
	HANDLE m_hLoadFile;
	HANDLE m_hCopyFile;
	OVERLAPPED m_loadOV;
	OVERLAPPED m_CopyOV;
	bool m_bLoadFinish = false;
	bool m_bWriteFinish = false;
public:
	void  FileInformation(HANDLE hFile);
};

