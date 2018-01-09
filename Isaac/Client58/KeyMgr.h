#pragma once

#include "define.h"

class CKeyMgr
{
DECLARE_SINGLETON(CKeyMgr)

private:
	DWORD		m_dwKey;
	DWORD		m_dwKeyPressed;
	DWORD		m_dwKeyPresseds[3];
	DWORD		m_dwKeyDown;

public:
	void	KeyCheck(void);
	bool	KeyPressed(DWORD _dwKey, int index);
	bool	KeyPressed(DWORD _dwKey);
	bool	KeyDown(DWORD _dwKey);
	bool	KeyCombine(DWORD _dwFirstKey, DWORD _dwSecondKey);

private:
	CKeyMgr(void);
	~CKeyMgr(void);
};
