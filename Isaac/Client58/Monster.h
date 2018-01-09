#pragma once
#include "obj.h"

class CMonster :
	public CObj
{
public:
	void WorldMatrix(void);
	void AStarMove(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CMonster(void);
	~CMonster(void);
};
