#pragma once
#include "boss.h"

class CSmallSteven :
	public CBoss
{
private:
	list<CObj*>* pObjList;
	bool m_bBulletFired;
	bool m_bCooldown;
	bool m_attacksound;
public:
	void FrameMove(void);
	void Tracking_Float(void);
	void Tracking_Rage(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CSmallSteven(void);
	~CSmallSteven(void);
};
