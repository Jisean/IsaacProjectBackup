#pragma once
#include "ui.h"

class CMinimap :
	public CUI
{
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CMinimap(void);
	~CMinimap(void);
};
