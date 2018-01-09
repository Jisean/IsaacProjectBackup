#include "StdAfx.h"
#include "Stage.h"
#include "ObjFactory.h"
#include "Player.h"
#include "TileMgr.h"
#include "UI.h"
#include "PassiveItem.h"
#include "Gaper.h"
#include "BlackFly.h"
#include "AttackFly.h"
#include "Horf.h"
#include "RedHost.h"
#include "BigSteven.h"
#include "SmallSteven.h"
#include "SoundMgr.h"

int g_iRoomMobCnt1 = 3;
int g_iRoomMobCnt2 = 12;
int g_iRoomMobCnt3 = 1;
int g_iRoomMobCnt4 = 5;
int g_iRoomMobCntBoss = 2;

CStage::CStage(void)
{
	m_bIntrostart = false;
	m_bIntroend = false;
	m_bBgmRoof = false;
	m_bShopintrostart = false;
	m_bShopintroend = false;
	m_bBossjingle = false;
	m_bBossRoofstart = false;
	m_bBosscalmintrostart = false;
	m_bBosscalmintroend = false;
	m_bBossjingle = false;
	m_bShopRoof = false;
	m_bBosscalmroof = false;

	dwBgmTime = GetTickCount();
}

CStage::~CStage(void)
{
	Release();
}

HRESULT CStage::Initialize(void)
{
	CObjMgr::GetInst()->AddObj(OBJ_UI,CObjFactory<CUI>::CreateObj());
	CObjMgr::GetInst()->AddObj(OBJ_PLAYER, CObjFactory<CPlayer>::CreateObj(D3DXVECTOR3(WINCX/2.f,WINCY/2.f,0.f)));
	////////////////////////////////////////////////////////////////////////////////////////
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CHorf>::CreateObj(D3DXVECTOR3(1289.f,170.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CHorf>::CreateObj(D3DXVECTOR3(1628.f,578.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CHorf>::CreateObj(D3DXVECTOR3(1901.f,170.f,0.f)));
	///////////////////////////////////////////////////////////////////////////////////////
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2310.f,170.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2376.f,170.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2310.f,237.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2376.f,237.f,0.f)));

	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2310.f,510.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2376.f,510.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2310.f,577.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2376.f,577.f,0.f)));

	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2991.f,170.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(3055.f,170.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2991.f,237.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(3055.f,237.f,0.f)));

	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2991.f,510.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(3055.f,510.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(2991.f,577.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CAttackFly>::CreateObj(D3DXVECTOR3(3055.f,577.f,0.f)));
	////////////////////////////////////////////////////////////////////////////////////////
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CGaper>::CreateObj(D3DXVECTOR3(3819.f,365.f,0.f)));
	//CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CGaper>::CreateObj(D3DXVECTOR3(3946.f,365.f,0.f)));
	////////////////////////////////////////////////////////////////////////////////////////
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CRedHost>::CreateObj(D3DXVECTOR3(4824.f,365.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CRedHost>::CreateObj(D3DXVECTOR3(4591.f,267.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CRedHost>::CreateObj(D3DXVECTOR3(4591.f,481.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CRedHost>::CreateObj(D3DXVECTOR3(5129.f,267.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_MONSTER, CObjFactory<CRedHost>::CreateObj(D3DXVECTOR3(5129.f,481.f,0.f)));
	////////////////////////////////////////////////////////////////////////////////////////
	CObjMgr::GetInst()->AddObj(OBJ_BOSS_BIG, CObjFactory<CBigSteven>::CreateObj(D3DXVECTOR3(6260.f,233.f,0.f)));
	CObjMgr::GetInst()->AddObj(OBJ_BOSS_SMALL, CObjFactory<CSmallSteven>::CreateObj(D3DXVECTOR3(6160.f,233.f,0.f)));
	////////////////////////////////////////////////////////////////////////////////////////
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(473.f,1120.f,0.f),PS_2020));
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(201.f,1120.f,0.f),PS_BOOM));
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(801.f,1120.f,0.f),PS_MEAT));
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(801.f,1220.f,0.f),PS_EPICFETUS));
	////////////////////////////////////////////////////////////////////////////////////////

	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(2953.f,1190.f,0.f),PS_SACREDHEART));
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(2817.f,1124.f,0.f),PS_PYRO));
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(2687.f,1190.f,0.f),PS_ROIDRAGE));
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(2545.f,1118.f,0.f),PS_BLOODBAG));
	CObjMgr::GetInst()->AddObj(OBJ_ITEM_PASSIVE, CObjFactory<CPassiveItem>::CreateObj(D3DXVECTOR3(2409.f,1190.f,0.f),PS_MUTANTSPIDER));
	////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}

int CStage::Progress(void)
{	
	CObjMgr::GetInst()->Progress();

	CTileMgr::GetInst()->Progress();

	if(*(CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].front()->GetRoomType()) !=12 && *(CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].front()->GetRoomType()) !=5)
	{
		m_bShopintrostart = false;
		m_bShopintroend = false;
		m_bShopRoof = false;

		m_bBossRoof = false;
		
		m_bBosscalmintrostart = false;
		m_bBosscalmintroend = false;
		m_bBosscalmroof = false;


		if(m_bIntrostart == false)
		{
			dwBgmTime = GetTickCount();
			CSoundMgr::GetInst()->PlayBgm(L"basementintro.ogg");
			m_bIntrostart = true;
		}
		if(dwBgmTime + 13700 < GetTickCount() && m_bIntroend == false)
		{
			m_bIntroend = true;
			CSoundMgr::GetInst()->PlayBgm(L"basement.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 116500 < GetTickCount() && m_bBgmRoof == false)
		{
			m_bBgmRoof = true;
			CSoundMgr::GetInst()->PlayBgm(L"basement.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 116500 < GetTickCount() && m_bBgmRoof == true)
		{
			m_bBgmRoof = false;
			CSoundMgr::GetInst()->PlayBgm(L"basement.ogg");
			dwBgmTime = GetTickCount();
		}
	}
	else if(*(CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].front()->GetRoomType()) ==12)
	{
		m_bIntrostart = false;
		m_bIntroend = false;
		m_bBgmRoof = false;

		if(m_bShopintrostart == false)
		{
			dwBgmTime = GetTickCount();
			CSoundMgr::GetInst()->PlayBgm(L"storeloopintro.ogg");
			m_bShopintrostart = true;
		}
		if(dwBgmTime + 8200 < GetTickCount() && m_bShopintroend == false)
		{
			m_bShopintroend = true;
			CSoundMgr::GetInst()->PlayBgm(L"storeloop.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 65900 < GetTickCount() && m_bShopRoof == false)
		{
			m_bShopRoof = true;
			CSoundMgr::GetInst()->PlayBgm(L"storeloop.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 65900 < GetTickCount() && m_bShopRoof == true)
		{
			m_bShopRoof = false;
			CSoundMgr::GetInst()->PlayBgm(L"storeloop.ogg");
			dwBgmTime = GetTickCount();
		}

	}

	else if(*(CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].front()->GetRoomType()) == 5)
	{
		m_bIntrostart = false;
		m_bIntroend = false;
		m_bBgmRoof = false;

		if(g_iRoomMobCntBoss !=0 && m_bBossRoofstart == false)
		{
			dwBgmTime = GetTickCount();
			CSoundMgr::GetInst()->PlayBgm(L"bossfight.ogg");
			m_bBossRoofstart = true;
		}
		if(dwBgmTime + 127900 < GetTickCount() && m_bBossRoof == false && g_iRoomMobCntBoss !=0)
		{
			m_bBossRoof = true;
			CSoundMgr::GetInst()->PlayBgm(L"bossfight.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 127900 < GetTickCount() && m_bBossRoof == true && g_iRoomMobCntBoss !=0)
		{
			m_bBossRoof = false;
			CSoundMgr::GetInst()->PlayBgm(L"bossfight.ogg");
			dwBgmTime = GetTickCount();
		}

		if(g_iRoomMobCntBoss == 0 && m_bBossjingle == false)
		{
			dwBgmTime = GetTickCount();
			CSoundMgr::GetInst()->EffectSound3(L"bossendjingle.ogg");
			m_bBossjingle = true;
		}

		if(g_iRoomMobCntBoss == 0 && m_bBossjingle == true && m_bBosscalmintrostart == false)
		{
			CSoundMgr::GetInst()->PlayBgm(L"thecalmintro.ogg");
			m_bBosscalmintrostart = true; 
			dwBgmTime = GetTickCount();
		}



		if(dwBgmTime + 8400 < GetTickCount() && m_bBosscalmintroend == false && g_iRoomMobCntBoss == 0)
		{
			m_bBosscalmintroend = true;
			CSoundMgr::GetInst()->PlayBgm(L"thecalm.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 116400 < GetTickCount() && m_bBosscalmroof == false && g_iRoomMobCntBoss == 0)
		{
			m_bBosscalmroof = true;
			CSoundMgr::GetInst()->PlayBgm(L"thecalm.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 116400 < GetTickCount() && m_bBosscalmroof == true && g_iRoomMobCntBoss == 0)
		{
			m_bBosscalmroof = false;
			CSoundMgr::GetInst()->PlayBgm(L"thecalm.ogg");
			dwBgmTime = GetTickCount();
		}



	}
	return 0;
}

void CStage::Render(void)
{
	CObjMgr::GetInst()->Render();
}

void CStage::Release(void)
{

}
