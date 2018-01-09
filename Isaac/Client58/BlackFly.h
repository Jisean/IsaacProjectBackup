#pragma once
#include "monster.h"

class CBlackFly :
	public CMonster
{
public:
	void FrameMove(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CBlackFly(void);
	~CBlackFly(void);
};
