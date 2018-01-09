#pragma once
#include "obj.h"

class CPlayer :
	public CObj
{
protected:
	bool			m_bHasBodynHead;
	bool			m_bBlinking;
	D3DXVECTOR3		m_vecOffset;
	map<wstring, UNITDATA*> m_mapStat;

public:
	CPlayer(void);
	~CPlayer(void);

public:
	void WorldMatrix(void);
	void KeyInput(void);
	void AStarMove(void);
	void Scroll(void);
	void DynamicScroll(void);
	void StatLoad(const wstring& wstrName);



public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
