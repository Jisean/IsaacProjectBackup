#pragma once
#include "monster.h"

class CHorf :
	public CMonster
{
private:
	bool m_bCooldown;
	bool m_bBulletFired;
	bool m_bAttacksound;
public:
	void FrameMove(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CHorf(void);
	~CHorf(void);
};
