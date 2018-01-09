#pragma once
#include "obj.h"

class CUI :
	public CObj
{
protected:
	int m_iCount;
protected:
	bool	m_bHasUI;
	bool	m_bIsBossRoom;
	bool	m_bIsDelete;
public:
	void WorldMatrix(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CUI(void);
	~CUI(void);
};
