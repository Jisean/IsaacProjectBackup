#pragma once
#include "obj.h"

class CTear :
	public CObj
{
private:
	wstring			m_wstrStateKey;
public:
	CTear(void);
	~CTear(void);
public:
	void WorldMatrix(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
};
