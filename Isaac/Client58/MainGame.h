#pragma once
#include "Include.h"

class CDevice;
class CSceneMgr;

class CMainGame
{
private:
	CDevice*	m_pDevice;
	CSceneMgr*	m_pScene;
	float		m_fTime;
	int			m_iCount;
	TCHAR		m_szFPS[MIN_STR];
	D3DXMATRIX	m_matTrans;

public:
	HRESULT		Initialize(void);
	void		Progress(void);
	void		Render(void);
	void		Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
