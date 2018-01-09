#include "StdAfx.h"
#include "ObjMgr.h"
#include "BackGround.h"
#include "Player.h"
#include "ObjFactory.h"
#include "FaceCostume.h"
#include "SoundMgr.h"
#include "HatCostume.h"

IMPLEMENT_SINGLETON(CObjMgr)

bool		g_DoubleShot = false;
bool		g_bTripleShot = false;
bool		g_bQurdShot = false;
bool		g_bGuideMode = false;
bool		g_bEpicFetus = false;


CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

HRESULT CObjMgr::Initialize(void)
{
	CObj*	pBackGround = CObjFactory<CBackGround>::CreateObj();
	m_ObjList[OBJ_BACK].push_back(pBackGround);
	pfx = 0.f;
	pfy = 0.f;


	return S_OK;
}

void CObjMgr::Progress(void)
{	
	int		iResult = 0;

	for(int i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			iResult = (*iter)->Progress();

			if(iResult == 1)
			{
				::Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}

			else
				++iter;
		}
	}

	PickupCheck();
	HeartCheck();
	PassiveCheck();
	TearCheck();
	TearBossCheck1();
	TearBossCheck2();
	BombCheck();
	BulletCheck();
	MobPlayerCheck();
	BombBossCheck1();
	BombBossCheck2();
	//PlayerCheck();
	MonsterCheck();
	BossCheck();

}

void CObjMgr::Render(void)
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			m_vecRender[(*iter)->GetRenderType()].push_back(*iter);
		}
	}
	sort(m_vecRender[R_WORLDOBJ].begin(),
		m_vecRender[R_WORLDOBJ].end(),
		CObjMgr::Compare);
	for(int i = 0; i < R_END; ++i)
	{
		for(int j = 0, iCnt = m_vecRender[i].size(); j < iCnt; ++j)
		{
			m_vecRender[i][j]->Render();
		}

		m_vecRender[i].clear();
	}

}

void CObjMgr::Release(void)
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DELETEOBJ());
		m_ObjList[i].clear();
	}


}

void CObjMgr::AddObj(OBJID _eID, CObj* pObj)
{
	m_ObjList[_eID].push_back(pObj);
}

const vector<TILE*>* CObjMgr::GetTile(void)
{
	return ((CBackGround*)m_ObjList[OBJ_BACK].front())->GetTile();
}
bool CObjMgr::Compare(CObj* pDest, CObj* pSource)
{
	return pDest->GetInfo()->vPos.y < pSource->GetInfo()->vPos.y;
}


void CObjMgr::PickupCheck(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_ITEM_PICKUP].begin();		
	for(iter; iter != m_ObjList[OBJ_ITEM_PICKUP].end(); ++iter)
	{
		if(m_ObjList[OBJ_PLAYER].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_PLAYER].begin();

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x + 10 / 2.f > fDistance)
		{
			PICKUP picktype;
			picktype = PICKUP(*((*iter)->GetItemName()));
			if(picktype == PICK_PENNY)
			{
				CSoundMgr::GetInst()->EffectSound3(L"pennypickup.wav");
				(*iter2)->SetCoin(1);
			}
			else if(picktype == PICK_BOMB)
			{
				CSoundMgr::GetInst()->EffectSound3(L"bombpickup1.wav");
				(*iter2)->SetBomb(1);
			}
			else if(picktype == PICK_DIME)
			{
				CSoundMgr::GetInst()->EffectSound3(L"dimepickup.wav");
				(*iter2)->SetCoin(10);
			}
			else if(picktype == PICK_DOUBLEBOMB)
			{
				CSoundMgr::GetInst()->EffectSound3(L"bombpickup2.wav");
				(*iter2)->SetBomb(2);
			}
			else if(picktype == PICK_DOUBLEKEY)
			{
				CSoundMgr::GetInst()->EffectSound3(L"keypickup.wav");
				(*iter2)->SetKey(2);
			}
			else if(picktype == PICK_KEY)
			{
				CSoundMgr::GetInst()->EffectSound3(L"keypickup.wav");
				(*iter2)->SetKey(1);
			}
			else if(picktype == PICK_NICKEL)
			{
				CSoundMgr::GetInst()->EffectSound3(L"nickelpickup.wav");
				(*iter2)->SetCoin(5);
			}
			else
				break;
			(*iter)->SetDead();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
		{
			PICKUP picktype;
			picktype = PICKUP(*((*iter)->GetItemName()));
			if(picktype == PICK_PENNY)
			{
				CSoundMgr::GetInst()->EffectSound3(L"pennypickup.wav");
				(*iter2)->SetCoin(1);
			}
			else if(picktype == PICK_BOMB)
			{
				CSoundMgr::GetInst()->EffectSound3(L"bombpickup1.wav");
				(*iter2)->SetBomb(1);
			}
			else if(picktype == PICK_DIME)
			{
				CSoundMgr::GetInst()->EffectSound3(L"dimepickup.wav");
				(*iter2)->SetCoin(10);
			}
			else if(picktype == PICK_DOUBLEBOMB)
			{
				CSoundMgr::GetInst()->EffectSound3(L"bombpickup2.wav");
				(*iter2)->SetBomb(2);
			}
			else if(picktype == PICK_DOUBLEKEY)
			{
				CSoundMgr::GetInst()->EffectSound3(L"keypickup.wav");
				(*iter2)->SetKey(2);
			}
			else if(picktype == PICK_KEY)
			{
				CSoundMgr::GetInst()->EffectSound3(L"keypickup.wav");
				(*iter2)->SetKey(1);
			}
			else if(picktype == PICK_NICKEL)
			{
				CSoundMgr::GetInst()->EffectSound3(L"nickelpickup.wav");
				(*iter2)->SetCoin(5);
			}
			else
				break;
			(*iter)->SetDead();
		}
	}
}


void CObjMgr::HeartCheck(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_PLAYER].begin();

	list<CObj*>::iterator pickiter = m_ObjList[OBJ_ITEM_PICKUP].begin();
	list<CObj*>::iterator pickiter_end = m_ObjList[OBJ_ITEM_PICKUP].end();


	for(pickiter; pickiter != pickiter_end; pickiter++)
	{

		float fWidth = (*iter)->GetInfo()->vSize.x / 2.f + (*pickiter)->GetInfo()->vSize.x + 10;
		float fHeight = (*iter)->GetInfo()->vSize.y / 2.f + (*pickiter)->GetInfo()->vSize.y + 10;

		float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*pickiter)->GetInfo()->vPos.x);
		float fDistY = fabs((*iter)->GetInfo()->vPos.y -(*pickiter)->GetInfo()->vPos.y);

		if(pfx != NULL && pfy != NULL)
		{
			pfx = fWidth - fDistX;
			pfy = fHeight - fDistY;
		}

		if(fDistX < fWidth && fDistY < fHeight)
		{
			if(*(*iter)->GetPlayerHp() != *(*iter)->GetPlayerMaxHP())
			{
				PICKUP picktype;
				picktype = PICKUP(*((*pickiter)->GetItemName()));
				if(pfy > pfx)
				{
					//가로
					if((*iter)->GetInfo()->vPos.x  < (*pickiter)->GetInfo()->vPos.x)
					{
						//왼쪽
						if(picktype == PICK_HEART)
							(*iter)->SetHP(1.f);
						else if(picktype == PICK_HALFHEART)
							(*iter)->SetHP(0.5f);
						else if(picktype == PICK_DOUBLEHEART)
							(*iter)->SetHP(2.f);
					}
					else
					{
						//오른쪽
						if(picktype == PICK_HEART)
							(*iter)->SetHP(1.f);
						else if(picktype == PICK_HALFHEART)
							(*iter)->SetHP(0.5f);
						else if(picktype == PICK_DOUBLEHEART)
							(*iter)->SetHP(2.f);
					}
					CSoundMgr::GetInst()->EffectSound3(L"heartpickup1.wav");
					(*pickiter)->SetDead();

				}
				else
				{
					//세로
					if((*iter)->GetInfo()->vPos.y  < (*pickiter)->GetInfo()->vPos.y)
					{
						//위
						if(picktype == PICK_HEART)
							(*iter)->SetHP(1.f);
						else if(picktype == PICK_HALFHEART)
							(*iter)->SetHP(0.5f);
						else if(picktype == PICK_DOUBLEHEART)
							(*iter)->SetHP(2.f);
					}
					else
					{
						//아래
						if(picktype == PICK_HEART)
							(*iter)->SetHP(1.f);
						else if(picktype == PICK_HALFHEART)
							(*iter)->SetHP(0.5f);
						else if(picktype == PICK_DOUBLEHEART)
							(*iter)->SetHP(2.f);
					}

					CSoundMgr::GetInst()->EffectSound3(L"heartpickup1.wav");
					(*pickiter)->SetDead();
				}
			}
			else
			{
				PICKUP picktype;
				picktype = PICKUP(*((*pickiter)->GetItemName()));
				if(pfy > pfx)
				{
					//가로
					if((*iter)->GetInfo()->vPos.x  < (*pickiter)->GetInfo()->vPos.x)
					{
						//왼쪽
						if(picktype == PICK_HEART || picktype == PICK_HALFHEART || picktype == PICK_DOUBLEHEART)
							(*pickiter)->GetInfo()->vPos.x += (*iter)->GetSpeed();
					}
					else
					{
						//오른쪽
						if(picktype == PICK_HEART || picktype == PICK_HALFHEART || picktype == PICK_DOUBLEHEART)
							(*pickiter)->GetInfo()->vPos.x -=(*iter)->GetSpeed();
					}
				}
				else
				{
					//세로
					if((*iter)->GetInfo()->vPos.y  < (*pickiter)->GetInfo()->vPos.y)
					{
						//위
						if(picktype == PICK_HEART || picktype == PICK_HALFHEART || picktype == PICK_DOUBLEHEART)
							(*pickiter)->GetInfo()->vPos.y += (*iter)->GetSpeed();
					}
					else
					{
						//아래
						if(picktype == PICK_HEART || picktype == PICK_HALFHEART || picktype == PICK_DOUBLEHEART)
							(*pickiter)->GetInfo()->vPos.y -=(*iter)->GetSpeed();
					}
				}
			}
		}
	}

}

void CObjMgr::PassiveCheck(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_ITEM_PASSIVE].begin();		
	for(iter; iter != m_ObjList[OBJ_ITEM_PASSIVE].end(); ++iter)
	{
		if(m_ObjList[OBJ_PLAYER].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_PLAYER].begin();

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x + 10 / 2.f > fDistance)
		{
			PASSIVEITEM passivename;
			passivename = PASSIVEITEM(*((*iter)->GetItemName()));
			if(passivename == PS_2020)
			{
				g_DoubleShot = true;
				g_bTripleShot = false;
				g_bQurdShot = false;
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_2020));
				CSoundMgr::GetInst()->EffectSound3(L"itempick4.wav");
			}
			if(passivename == PS_INNEREYE)
			{
				g_DoubleShot = false;
				g_bTripleShot = true;
				g_bQurdShot = false;
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_INNEREYE));
				CSoundMgr::GetInst()->EffectSound3(L"itempick4.wav");
			}
			if(passivename == PS_MUTANTSPIDER)
			{
				g_DoubleShot = false;
				g_bTripleShot = false;
				g_bQurdShot = true;
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_MUTANTSPIDER));
				CSoundMgr::GetInst()->EffectSound3(L"itempick4.wav");
			}
			else if(passivename == PS_BLOODBAG)
			{
				(*iter2)->SetMaxHp(3);
				(*iter2)->SetHP(3.f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_BLOODBAG));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_MEAT)
			{
				(*iter2)->SetMaxHp(1);
				(*iter2)->SetHP(1.f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_MEAT));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_SACREDHEART)
			{
				(*iter2)->SetTear(1.5f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_SACREDHEART));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_EPICFETUS)
			{
				g_bEpicFetus = true;
				(*iter2)->SetTear(1.5f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_HAT,
					CObjFactory<CHatCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_EPICFETUS));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_ROIDRAGE)
			{
				(*iter2)->SetSpeed(1.f);
				CSoundMgr::GetInst()->EffectSound3(L"itempick2.wav");
			}
			else if(passivename == PS_PYRO)
			{
				(*iter2)->SetBomb(99);
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_BOOM)
			{
				(*iter2)->SetBomb(10);
				CSoundMgr::GetInst()->EffectSound3(L"itempick3.wav");
			}
			(*iter)->SetDead();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
		{
			PASSIVEITEM passivename;
			passivename = PASSIVEITEM(*((*iter)->GetItemName()));
			if(passivename == PS_2020)
			{
				g_DoubleShot = true;
				g_bTripleShot = false;
				g_bQurdShot = false;
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_2020));
				CSoundMgr::GetInst()->EffectSound3(L"itempick4.wav");
			}
			if(passivename == PS_INNEREYE)
			{
				g_DoubleShot = false;
				g_bTripleShot = true;
				g_bQurdShot = false;
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_INNEREYE));
				CSoundMgr::GetInst()->EffectSound3(L"itempick4.wav");
			}
			if(passivename == PS_MUTANTSPIDER)
			{
				g_DoubleShot = false;
				g_bTripleShot = false;
				g_bQurdShot = true;
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_MUTANTSPIDER));
				CSoundMgr::GetInst()->EffectSound3(L"itempick4.wav");
			}
			else if(passivename == PS_BLOODBAG)
			{
				(*iter2)->SetMaxHp(3);
				(*iter2)->SetHP(3.f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_BLOODBAG));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_MEAT)
			{
				(*iter2)->SetMaxHp(1);
				(*iter2)->SetHP(1.f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_MEAT));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_SACREDHEART)
			{
				(*iter2)->SetTear(1.5f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_FACE,
					CObjFactory<CFaceCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_SACREDHEART));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_EPICFETUS)
			{
				(*iter2)->SetTear(1.5f);
				CObjMgr::GetInst()->AddObj(OBJ_COSTUME_HAT,
					CObjFactory<CHatCostume>::
					CreateObj2((*iter2)->GetInfo()->vPos.x + 1, 
					(*iter2)->GetInfo()->vPos.y - 26.5f, PS_EPICFETUS));
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_ROIDRAGE)
			{
				(*iter2)->SetSpeed(1.f);
				CSoundMgr::GetInst()->EffectSound3(L"itempick2.wav");
			}
			else if(passivename == PS_PYRO)
			{
				(*iter2)->SetBomb(99);
				CSoundMgr::GetInst()->EffectSound3(L"itempick1.wav");
			}
			else if(passivename == PS_BOOM)
			{
				(*iter2)->SetBomb(10);
				CSoundMgr::GetInst()->EffectSound3(L"itempick3.wav");
			}
			(*iter)->SetDead();
		}
	}
}

void CObjMgr::TearCheck(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();		
	for(iter; iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		if(m_ObjList[OBJ_TEAR].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_TEAR].begin();

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		/////////////////////////////////

		//cout << "Distance " << fDistance << endl;
		//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
		//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
		/////////////////////////////////
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance)
		{
			FIREWAY fireway;
			fireway = FIREWAY(*((*iter2)->GetFireWay()));

			if(fireway == WAY_LEFT)
			{
				(*iter)->GetInfo()->vPos.x -= 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			else if(fireway == WAY_RIGHT)
			{
				(*iter)->GetInfo()->vPos.x += 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			else if(fireway == WAY_UP)
			{
				(*iter)->GetInfo()->vPos.y -= 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			else if(fireway == WAY_DOWN)
			{
				(*iter)->GetInfo()->vPos.y += 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			(*iter2)->SetDead();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
		{
			FIREWAY fireway;
			fireway = FIREWAY(*((*iter2)->GetFireWay()));
			if(fireway == WAY_LEFT)
			{
				(*iter)->GetInfo()->vPos.x -= 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			else if(fireway == WAY_RIGHT)
			{
				(*iter)->GetInfo()->vPos.x += 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			else if(fireway == WAY_UP)
			{
				(*iter)->GetInfo()->vPos.y -= 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			else if(fireway == WAY_DOWN)
			{
				(*iter)->GetInfo()->vPos.y += 15.f;
				(*iter)->SetMonHp(-1.f);
			}
			(*iter2)->SetDead();
		}
	}
}

void CObjMgr::MonsterCheck(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
	list<CObj*>::iterator iter2 =m_ObjList[OBJ_MONSTER].begin();
	for(iter; iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		if(m_ObjList[OBJ_MONSTER].size() <= 0)
			break;
		for(iter2; iter2 != m_ObjList[OBJ_MONSTER].end(); ++iter2)
		{
			if(iter == iter2)
				break;

			float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
			float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
			float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
			fDistance = sqrt(fDistance);
			/////////////////////////////////
			//cout << "Distance " << fDistance << endl;
			//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
			//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
			/////////////////////////////////
			if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance)
			{
				if((*iter)->GetInfo()->vDir.x > 0)
				{
					(*iter)->GetInfo()->vPos.x -= *(*iter)->GetMonsterSpeed(); 
					(*iter2)->GetInfo()->vPos.x += *(*iter2)->GetMonsterSpeed();
				}
				else if((*iter)->GetInfo()->vDir.x < 0)
				{
					(*iter)->GetInfo()->vPos.x += *(*iter)->GetMonsterSpeed();
					(*iter2)->GetInfo()->vPos.x -= *(*iter2)->GetMonsterSpeed();
				}
				else if((*iter)->GetInfo()->vDir.y > 0)
				{
					(*iter)->GetInfo()->vPos.y += *(*iter)->GetMonsterSpeed();
					(*iter2)->GetInfo()->vPos.y -= *(*iter2)->GetMonsterSpeed();
				}
				else if((*iter)->GetInfo()->vDir.y < 0)
				{
					(*iter)->GetInfo()->vPos.y -= *(*iter)->GetMonsterSpeed();
					(*iter2)->GetInfo()->vPos.y += *(*iter2)->GetMonsterSpeed();
				}
			}
			else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
			{
				if((*iter)->GetInfo()->vDir.x > 0)
				{
					(*iter)->GetInfo()->vPos.x -= *(*iter)->GetMonsterSpeed();
					(*iter2)->GetInfo()->vPos.x += *(*iter2)->GetMonsterSpeed();
				}
				else if((*iter)->GetInfo()->vDir.x < 0)
				{
					(*iter)->GetInfo()->vPos.x += *(*iter)->GetMonsterSpeed();
					(*iter2)->GetInfo()->vPos.x -= *(*iter2)->GetMonsterSpeed();
				}
				else if((*iter)->GetInfo()->vDir.y > 0)
				{
					(*iter)->GetInfo()->vPos.y += *(*iter)->GetMonsterSpeed();
					(*iter2)->GetInfo()->vPos.y -= *(*iter2)->GetMonsterSpeed();
				}
				else if((*iter)->GetInfo()->vDir.y < 0)
				{
					(*iter)->GetInfo()->vPos.y -= *(*iter)->GetMonsterSpeed();
					(*iter2)->GetInfo()->vPos.y += *(*iter2)->GetMonsterSpeed();
				}
			}
		}
	}
}

void CObjMgr::TearBossCheck1(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_BOSS_BIG].begin();		
	for(iter; iter != m_ObjList[OBJ_BOSS_BIG].end(); ++iter)
	{
		if(m_ObjList[OBJ_TEAR].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_TEAR].begin();

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		/////////////////////////////////

		//cout << "Distance " << fDistance << endl;
		//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
		//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
		/////////////////////////////////
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance)
		{
			FIREWAY fireway;
			fireway = FIREWAY(*((*iter2)->GetFireWay()));

			if(fireway == WAY_LEFT)
			{
				(*iter)->GetInfo()->vPos.x -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_RIGHT)
			{
				(*iter)->GetInfo()->vPos.x += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_UP)
			{
				(*iter)->GetInfo()->vPos.y -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_DOWN)
			{
				(*iter)->GetInfo()->vPos.y += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			(*iter2)->SetDead();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
		{
			FIREWAY fireway;
			fireway = FIREWAY(*((*iter2)->GetFireWay()));
			if(fireway == WAY_LEFT)
			{
				(*iter)->GetInfo()->vPos.x -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_RIGHT)
			{
				(*iter)->GetInfo()->vPos.x += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_UP)
			{
				(*iter)->GetInfo()->vPos.y -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_DOWN)
			{
				(*iter)->GetInfo()->vPos.y += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			(*iter2)->SetDead();
		}
	}
}
void CObjMgr::TearBossCheck2(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_BOSS_SMALL].begin();		
	for(iter; iter != m_ObjList[OBJ_BOSS_SMALL].end(); ++iter)
	{
		if(m_ObjList[OBJ_TEAR].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_TEAR].begin();

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		/////////////////////////////////

		//cout << "Distance " << fDistance << endl;
		//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
		//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
		/////////////////////////////////
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance)
		{
			FIREWAY fireway;
			fireway = FIREWAY(*((*iter2)->GetFireWay()));

			if(fireway == WAY_LEFT)
			{
				(*iter)->GetInfo()->vPos.x -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_RIGHT)
			{
				(*iter)->GetInfo()->vPos.x += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_UP)
			{
				(*iter)->GetInfo()->vPos.y -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;

			}
			else if(fireway == WAY_DOWN)
			{
				(*iter)->GetInfo()->vPos.y += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			(*iter2)->SetDead();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
		{
			FIREWAY fireway;
			fireway = FIREWAY(*((*iter2)->GetFireWay()));
			if(fireway == WAY_LEFT)
			{
				(*iter)->GetInfo()->vPos.x -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_RIGHT)
			{
				(*iter)->GetInfo()->vPos.x += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_UP)
			{
				(*iter)->GetInfo()->vPos.y -= 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			else if(fireway == WAY_DOWN)
			{
				(*iter)->GetInfo()->vPos.y += 15.f;
				(*iter)->SetMonHp(-1.f);
				--g_iBossTotalHp;
			}
			(*iter2)->SetDead();
		}
	}
}

void CObjMgr::BombCheck(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();		
	for(iter; iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		if(m_ObjList[OBJ_MONSTER].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_EFFECT_EXPLOSION].begin();
		if(m_ObjList[OBJ_EFFECT_EXPLOSION].size() <= 0)
			break;

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x + 50;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y + 50;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		/////////////////////////////////

		//cout << "Distance " << fDistance << endl;
		//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
		//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
		/////////////////////////////////
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance)
		{
			(*iter)->SetDead();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
		{
			(*iter)->SetDead();
		}
	}
}
void CObjMgr::BulletCheck(void)
{
	srand((unsigned)time(NULL));
	list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET].begin();		
	for(iter; iter != m_ObjList[OBJ_BULLET].end(); ++iter)
	{
		if(m_ObjList[OBJ_BULLET].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_PLAYER].begin();
		list<CObj*>::iterator iter2_head =m_ObjList[OBJ_PLAYER_HEAD].begin();
		list<CObj*>::iterator iter2_body =m_ObjList[OBJ_PLAYER_BODY].begin();

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		/////////////////////////////////

		//cout << "Distance " << fDistance << endl;
		//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
		//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
		/////////////////////////////////
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance && *(*iter2)->GetInvincible() == false)
		{
			if(rand()%2 ==0)
				CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
			else
				CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
			(*iter2)->SetHP(-0.5f);
			(*iter2)->SetInvincible();
			(*iter2_body)->SetInvincible();
			(*iter2_head)->SetInvincible();
			(*iter)->SetDead();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance && *(*iter2)->GetInvincible() == false)
		{
			if(rand()%2 ==0)
				CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
			else
				CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
			(*iter2)->SetHP(-0.5f);
			(*iter2)->SetInvincible();
			(*iter2_body)->SetInvincible();
			(*iter2_head)->SetInvincible();
			(*iter)->SetDead();
		}
	}
}

void CObjMgr::MobPlayerCheck(void)
{
	srand((unsigned)time(NULL));
	list<CObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();		
	for(iter; iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		if(m_ObjList[OBJ_MONSTER].size() <= 0)
			break;

		list<CObj*>::iterator iter2 =m_ObjList[OBJ_PLAYER].begin();

		float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
		float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
		fDistance = sqrt(fDistance);
		/////////////////////////////////

		//cout << "Distance " << fDistance << endl;
		//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
		//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
		/////////////////////////////////
		if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance && *(*iter2)->GetInvincible() == false)
		{
			if(rand()%2 ==0)
				CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
			else
				CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
			(*iter2)->SetHP(-0.5f);
			(*iter2)->SetInvincible();
		}
		else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance && *(*iter2)->GetInvincible() == false)
		{
			if(rand()%2 ==0)
				CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
			else
				CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
			(*iter2)->SetHP(-0.5f);
			(*iter2)->SetInvincible();
		}
	}
}

void CObjMgr::BombBossCheck1(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_BOSS_BIG].begin();		
	if(m_ObjList[OBJ_BOSS_BIG].size() <= 0)
		return;

	list<CObj*>::iterator iter2 =m_ObjList[OBJ_EFFECT_EXPLOSION].begin();
	if(m_ObjList[OBJ_EFFECT_EXPLOSION].size() <= 0)
		return;

	float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x + 50;
	float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y + 50;
	float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
	fDistance = sqrt(fDistance);
	/////////////////////////////////

	//cout << "Distance " << fDistance << endl;
	//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
	//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
	/////////////////////////////////
	if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance && *(*iter)->GetInvincible() == false)
	{
		(*iter)->SetMonHp(-3.f);
		(*iter)->SetInvincible();
	}
	else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance && *(*iter)->GetInvincible() == false)
	{
		(*iter)->SetMonHp(-3.f);
		(*iter)->SetInvincible();
	}
}
void CObjMgr::BombBossCheck2(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_BOSS_SMALL].begin();		
	if(m_ObjList[OBJ_BOSS_SMALL].size() <= 0)
		return;

	list<CObj*>::iterator iter2 =m_ObjList[OBJ_EFFECT_EXPLOSION].begin();
	if(m_ObjList[OBJ_EFFECT_EXPLOSION].size() <= 0)
		return;

	float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x + 50;
	float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y + 50;
	float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
	fDistance = sqrt(fDistance);
	/////////////////////////////////

	//cout << "Distance " << fDistance << endl;
	//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
	//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
	/////////////////////////////////
	if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance && *(*iter)->GetInvincible() == false)
	{
		(*iter)->SetMonHp(-3.f);
		g_iBossTotalHp -= 3;
		(*iter)->SetInvincible();
	}
	else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance && *(*iter)->GetInvincible() == false)
	{
		(*iter)->SetMonHp(-3.f);
		g_iBossTotalHp -= 3;
		(*iter)->SetInvincible();
	}
}

void CObjMgr::BossCheck(void)
{
	list<CObj*>::iterator iter = m_ObjList[OBJ_BOSS_SMALL].begin();
	list<CObj*>::iterator iter2 =m_ObjList[OBJ_BOSS_BIG].begin();

	if(m_ObjList[OBJ_BOSS_BIG].size() <= 0)
		return;

	float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
	float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
	float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
	fDistance = sqrt(fDistance);
	/////////////////////////////////
	//cout << "Distance " << fDistance << endl;
	//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
	//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
	/////////////////////////////////
	if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance)
	{
		if((*iter)->GetInfo()->vDir.x > 0)
		{
			(*iter)->GetInfo()->vPos.x -= *(*iter)->GetMonsterSpeed(); 
		}
		else if((*iter)->GetInfo()->vDir.x < 0)
		{
			(*iter)->GetInfo()->vPos.x += *(*iter)->GetMonsterSpeed();
		}
		else if((*iter)->GetInfo()->vDir.y > 0)
		{
			(*iter)->GetInfo()->vPos.y += *(*iter)->GetMonsterSpeed();
		}
		else if((*iter)->GetInfo()->vDir.y < 0)
		{
			(*iter)->GetInfo()->vPos.y -= *(*iter)->GetMonsterSpeed();
		}
	}
	else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
	{
		if((*iter)->GetInfo()->vDir.x > 0)
		{
			(*iter)->GetInfo()->vPos.x -= *(*iter)->GetMonsterSpeed();
		}
		else if((*iter)->GetInfo()->vDir.x < 0)
		{
			(*iter)->GetInfo()->vPos.x += *(*iter)->GetMonsterSpeed();
		}
		else if((*iter)->GetInfo()->vDir.y > 0)
		{
			(*iter)->GetInfo()->vPos.y += *(*iter)->GetMonsterSpeed();
		}
		else if((*iter)->GetInfo()->vDir.y < 0)
		{
			(*iter)->GetInfo()->vPos.y -= *(*iter)->GetMonsterSpeed();
		}
	}
}