#pragma once
#include "item.h"

class CPickup :
	public CItem
{
private:
	bool m_bPickupLoad;
	FRAME m_tStartFrame;
public:
	void FrameMove(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CPickup(void);
	~CPickup(void);
};
