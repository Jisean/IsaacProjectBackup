#pragma once
#include "player.h"

class CPlayer_Body :
	public CPlayer
{
private:
	list<CObj*>* pObjList;
public:
	void FrameMove(void);
	void StateKeyInput(void);
public:
	CPlayer_Body(void);
	~CPlayer_Body(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
