#include "StdAfx.h"
#include "BigSteven.h"
#include "ObjFactory.h"
#include "ObjMgr.h"
#include "Astar.h"
#include "BigStevenBody.h"
#include "BigStevenHead.h"
#include "SoundMgr.h"
CBigSteven::CBigSteven(void)
{
}

CBigSteven::~CBigSteven(void)
{
}
HRESULT CBigSteven::Initialize(void)
{
	fHp = 40.f;
	iMaxHp = 40;
	m_tInfo.vSize = D3DXVECTOR3(66.f, 76.f, 0.f);
	m_fSpeed = 200.f;
	m_RenderType = R_WORLDOBJ;
	m_RoomType = 5;
	m_bHasBodynHead = false;
	b_soundroar = false;;
	m_bTired = true;
	m_bTrack_Walk = false;
	m_bTrack_Run = false;
	bInvincible = false;
	return S_OK;
}

int CBigSteven::Progress(void)
{
	srand((unsigned)time(NULL));
	if(m_bIsDead == true)
	{
		if(CObjMgr::GetInst()->GetObjList()[OBJ_BOSS_HEAD].size() == 0 && CObjMgr::GetInst()->GetObjList()[OBJ_BOSS_BODY].size() == 0)
		{
			--g_iRoomMobCntBoss;
			CSoundMgr::GetInst()->Monster5Sound(L"bossdeath.wav");
			return 1;
		}
	}
	if(m_bHasBodynHead == false)
	{
		CObjMgr::GetInst()->AddObj(OBJ_BOSS_BODY, 
			CObjFactory<CBigStevenBody>::CreateObj(m_tInfo.vPos));
		CObjMgr::GetInst()->AddObj(OBJ_BOSS_HEAD, 
			CObjFactory<CBigStevenHead>::CreateObj(m_tInfo.vPos.x + 1, m_tInfo.vPos.y - 26.5f));

		m_bHasBodynHead = true;
	}
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	CBoss::WorldMatrix();
	if(*(*iter)->GetRoomType() == m_RoomType)
	{
		if(m_bTrack_Walk == false && m_bTrack_Run == false && m_bTired == true)
		{
			CAStar::GetInst()->AStarStartPos(m_tInfo.vPos, (*iter)->GetInfo()->vPos);
			m_fSpeed = 200.f;
			CBoss::AStarMove();
			if(m_dwTime + 3000 < GetTickCount())
			{
				m_bTrack_Walk = true;
				m_bTired = false;
				m_dwTime = GetTickCount();
				
			}
		}
		else if(m_bTrack_Walk == true && m_bTrack_Run == false && m_bTired == false)
		{
			if(b_soundroar == false)
			{
				if(rand()%2 == 0)
					CSoundMgr::GetInst()->Monster5Sound(L"bossrun1.wav");
				else
					CSoundMgr::GetInst()->Monster5Sound(L"bossrun2.wav");
				b_soundroar = true;
			}
			CAStar::GetInst()->AStarStartPos(m_tInfo.vPos, (*iter)->GetInfo()->vPos);
			m_fSpeed = 200.f;
			CBoss::AStarMove();
			if(m_dwTime + 5000 < GetTickCount())
			{
				m_bTrack_Run = true;
				m_bTrack_Walk = false;
				m_dwTime = GetTickCount();
				
			}
		}
		else if(m_bTrack_Walk == false && m_bTrack_Run == true && m_bTired == false)
		{
			if(m_dwTime + 3000 < GetTickCount())
			{
				m_bTired = true;
				m_bTrack_Run = false;
				b_soundroar = false;
				m_dwTime = GetTickCount();
				
			}
		}

	}

	if(bInvincible == true)
	{
		if(m_dwTime + 1500 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}

	return 0;
}

void CBigSteven::Render(void)
{
	CBoss::Render();
}
void CBigSteven::Release(void)
{
}