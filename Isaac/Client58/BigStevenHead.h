#pragma once
#include "bigsteven.h"

class CBigStevenHead :
	public CBigSteven
{
private:
	list<CObj*>* pObjList;
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
	CBigStevenHead(void);
	~CBigStevenHead(void);
};
