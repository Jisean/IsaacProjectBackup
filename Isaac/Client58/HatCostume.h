#pragma once
#include "player.h"

class CHatCostume :
	public CPlayer
{
private:
	FRAME m_tStartFrame;
	list<CObj*>* pObjList;
	float	m_fFramespeed;
	bool	m_bCostumeLoad;

public:
	void FrameMove(void);
	void StateKeyInput(void);
public:
	CHatCostume(void);
	~CHatCostume(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
