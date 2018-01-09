#pragma once
#include "obj.h"

class CBomb :
	public CObj
{
public:
	void WorldMatrix(void);
	void FrameMove(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CBomb(void);
	~CBomb(void);
};
