#pragma once
#include "monster.h"

class CRedHost :
	public CMonster
{
private:
	bool m_bCooldown;
	bool m_bBulletFired;
public:
	void FrameMove(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CRedHost(void);
	~CRedHost(void);
};
