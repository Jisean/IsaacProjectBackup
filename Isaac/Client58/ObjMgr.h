#pragma once

#include "Include.h"

class CObj;
class CObjMgr
{
DECLARE_SINGLETON(CObjMgr)

private:
	list<CObj*>		m_ObjList[OBJ_END];
	vector<CObj*>	m_vecRender[R_END];
	float pfx;
	float pfy;

public:

	static bool Compare(CObj* pDest, CObj* pSource);
	void AddObj(OBJID _eID, CObj* pObj);

	const vector<TILE*>* GetTile(void);

	HRESULT Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);
	list<CObj*>*	GetObjList(void)
	{
		return m_ObjList;
	}
	void PickupCheck(void);
	void HeartCheck(void);
	void PassiveCheck(void);
	void TearCheck(void);
	void MonsterCheck(void);
	void TearBossCheck1(void);
	void TearBossCheck2(void);
	void BombCheck(void);
	void BulletCheck(void);
	void MobPlayerCheck(void);
	void BombBossCheck1(void);
	void BombBossCheck2(void);
	void BossCheck(void);
	
private:
	CObjMgr(void);
	~CObjMgr(void);
};
