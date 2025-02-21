#pragma once
#include "TGameCore.h"
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
	void   FileWrite(const TCHAR* filename);
	void   FileRead(const TCHAR* filename);
	void   Load(const TCHAR* filename);
	void   Copy(const TCHAR* filename);
	void   AsyncLoad(const TCHAR* filename);
	void   AsyncCopy(const TCHAR* filename);

	HANDLE m_hLoadFile;
	HANDLE m_hCopyFile;
	OVERLAPPED m_loadOV;
	OVERLAPPED m_CopyOV;
	bool m_bLoadFinish = false;
	bool m_bWriteFinish = false;
public:
	void  FileInformation(HANDLE hFile);
};

