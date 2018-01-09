#pragma once
#include "obj.h"

class CBullet :
	public CObj
{
private:
	wstring			m_wstrStateKey;
public:
	CBullet(void);
	~CBullet(void);
public:
	void WorldMatrix(void);
	void InnerProduct(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
};
