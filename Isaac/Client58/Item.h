#pragma once
#include "obj.h"

class CItem :
	public CObj
{
public:
	void WorldMatrix(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CItem(void);
	~CItem(void);
};
