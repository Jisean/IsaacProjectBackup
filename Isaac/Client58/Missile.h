#pragma once
#include "obj.h"

class CMissile :
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
	CMissile(void);
	~CMissile(void);
};
