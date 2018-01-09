#pragma once
#include "monster.h"

class CGaper :
	public CMonster
{
private:
	float fPrevDirX;
	float fPrevDirY;
public:
	void FrameMove(void);
	void AStarState(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CGaper(void);
	~CGaper(void);
};
