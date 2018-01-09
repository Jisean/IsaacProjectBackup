#pragma once
#include "obj.h"

class CEffect :
	public CObj
{
private:
	bool m_bEffectLoad;
public:
	void WorldMatrix(void);
	void FrameMove(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CEffect(void);
	~CEffect(void);
};
