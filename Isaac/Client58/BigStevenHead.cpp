#include "StdAfx.h"
#include "BigStevenHead.h"
#include "ObjMgr.h"

CBigStevenHead::CBigStevenHead(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CBigStevenHead::~CBigStevenHead(void)
{
}
HRESULT CBigStevenHead::Initialize(void)
{
	m_wstrObjKey = L"Boss";
	m_wstrStateKey = L"BigStevenHead";
	m_tFrame = FRAME(0.f, 0.f, 1.f);
	m_dwState = BOSS_STAND;
	m_dwPrevState = BOSS_STAND;
	m_RenderType = R_WORLDOBJ_HEAD;
	return S_OK;
}

int CBigStevenHead::Progress(void)
{
	if(m_bIsDead == true)
		return 1;
	FrameMove();
	list<CObj*>::iterator iter = pObjList[OBJ_BOSS_BIG].begin();
	m_tInfo.vPos.x = (*iter)->GetInfo()->vPos.x + 1.f;
	m_tInfo.vPos.y = (*iter)->GetInfo()->vPos.y - 30.5f;
	m_tInfo.vDir = (*iter)->GetInfo()->vDir;
	m_bTired = *(*iter)->GetBossTired();
	m_bTrack_Run = *(*iter)->GetBossRun();
	m_bTrack_Walk = *(*iter)->GetBossWalk();
	m_bIsDead = *(*iter)->GetDeadState();
	CBoss::WorldMatrix();
	AStarState();
	//cout << "head X : " << m_tInfo.vPos.x << endl;
	//cout << "head Y : " << m_tInfo.vPos.y << endl;
	return 0;
}

void CBigStevenHead::Render(void)
{
	CBoss::Render();
}

void CBigStevenHead::Release(void)
{

}
void CBigStevenHead::FrameMove(void)
{
	
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case BOSS_STAND:
			m_wstrStateKey = L"BigStevenHead";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case BOSS_TRACK_UD:
			m_wstrStateKey = L"BigStevenHead";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case BOSS_TRACK_LEFT:
			m_wstrStateKey = L"BigStevenHead";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case BOSS_TRACK_RIGHT:
			m_wstrStateKey = L"BigStevenHead";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case BOSS_TRACK_RUN_UD:
			m_wstrStateKey = L"BigStevenHead_Run";
			m_tFrame = FRAME(0.f, 10.f, 3.f);
			break;
		case BOSS_TRACK_RUN_LEFT:
			m_wstrStateKey = L"BigStevenHead_Run";
			m_tFrame = FRAME(0.f, 10.f, 3.f);
			break;
		case BOSS_TRACK_RUN_RIGHT:
			m_wstrStateKey = L"BigStevenHead_Run";
			m_tFrame = FRAME(0.f, 10.f, 3.f);
			break;
		case BOSS_TIRED:
			m_wstrStateKey = L"BigStevenHead_Tired";
			m_tFrame = FRAME(0.f, 8.f, 4.f);
			break;
		}
		m_dwPrevState = m_dwState;
	}

	
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(m_dwState != BOSS_STAND)
		{
			m_dwState = BOSS_STAND;
		}
		
		m_tFrame.fFrame = 0.f;
	}

}

void CBigStevenHead::AStarState(void)
{
	fPrevDirX = m_tInfo.vDir.x;
	fPrevDirY = m_tInfo.vDir.y;
	if(m_tInfo.vDir.x > 0 && (m_tInfo.vDir.y < 1.f || m_tInfo.vDir.y > -1.f || m_tInfo.vDir.y < -9999.f || m_tInfo.vDir.y > 9999.f))
	{
		if(m_bTired == true)
			m_dwState = BOSS_TRACK_RIGHT;
		else if(m_bTrack_Walk == true)
			m_dwState = BOSS_TRACK_RUN_RIGHT;
		else if(m_bTrack_Run == true)
			m_dwState = BOSS_TIRED;
	}	
	else if(m_tInfo.vDir.x < 0 && (m_tInfo.vDir.y < 1.f || m_tInfo.vDir.y > -1.f || m_tInfo.vDir.y < -9999.f || m_tInfo.vDir.y > 9999.f))
	{
		if(m_bTired == true)
			m_dwState = BOSS_TRACK_LEFT;
		else if(m_bTrack_Walk == true)
			m_dwState = BOSS_TRACK_RUN_LEFT;
		else if(m_bTrack_Run == true)
			m_dwState = BOSS_TIRED;
	}
	else if(m_tInfo.vDir.y > 0 && (m_tInfo.vDir.x < 1.f || m_tInfo.vDir.x > -1.f || m_tInfo.vDir.x < -9999.f || m_tInfo.vDir.x > 9999.f))
	{
		if(m_bTired == true)
			m_dwState = BOSS_TRACK_UD;
		else if(m_bTrack_Walk == true)
			m_dwState = BOSS_TRACK_RUN_UD;
		else if(m_bTrack_Run == true)
			m_dwState = BOSS_TIRED;
	}
	else if(m_tInfo.vDir.y < 0 && (m_tInfo.vDir.x < 1.f || m_tInfo.vDir.x > -1.f || m_tInfo.vDir.x < -9999.f || m_tInfo.vDir.x > 9999.f))
	{
		if(m_bTired == true)
			m_dwState = BOSS_TRACK_UD;
		else if(m_bTrack_Walk == true)
			m_dwState = BOSS_TRACK_RUN_UD;
		else if(m_bTrack_Run == true)
			m_dwState = BOSS_TIRED;
	}

	else if(fPrevDirX == m_tInfo.vDir.x && fPrevDirY == m_tInfo.vDir.y)
	{
		m_dwState = MS_STAND;
	}


}