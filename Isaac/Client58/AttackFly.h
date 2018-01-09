#pragma once
#include "monster.h"

class CAttackFly :
	public CMonster
{
public:
	void FrameMove(void);
	void Tracking(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAttackFly(void);
	~CAttackFly(void);
};
