#pragma once
#include "scene.h"

class CLogo :
	public CScene
{
private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
	RECT				rcLDBar;

public:
	CLogo(void);
	~CLogo(void);

public:
	static unsigned int __stdcall LoadThread(void* pArg);
	CRITICAL_SECTION	GetCrt(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
