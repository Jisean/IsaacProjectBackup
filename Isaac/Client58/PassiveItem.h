#pragma once
#include "item.h"

class CPassiveItem :
	public CItem
{
private:
	bool m_bPassiveLoad;
public:
	void ItemLoad();
	void FrameMove();
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CPassiveItem(void);
	~CPassiveItem(void);
};
