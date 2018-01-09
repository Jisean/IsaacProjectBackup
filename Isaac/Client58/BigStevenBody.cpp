#include "StdAfx.h"
#include "BigStevenBody.h"
#include "ObjMgr.h"


CBigStevenBody::CBigStevenBody(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CBigStevenBody::~CBigStevenBody(void)
{
}
HRESULT CBigStevenBody::Initialize(void)
{
	m_wstrObjKey = L"Boss";
	m_wstrStateKey = L"BigStevenBody_Walk_UD";
	m_dwState = BOSS_STAND;
	m_dwPrevState = BOSS_STAND;
	m_tFrame = FRAME(2.f, 0.f, 10.f);
	m_RenderType = R_WORLDOBJ_BODY;
	return S_OK;
}

int CBigStevenBody::Progress(void)
{
	if(m_bIsDead == true)
		return 1;
	FrameMove();
	list<CObj*>::iterator iter = pObjList[OBJ_BOSS_BIG].begin();
	m_tInfo.vPos = (*iter)->GetInfo()->vPos;
	m_tInfo.vDir = (*iter)->GetInfo()->vDir;
	m_bTired = *(*iter)->GetBossTired();
	m_bTrack_Run = *(*iter)->GetBossRun();
	m_bTrack_Walk = *(*iter)->GetBossWalk();
	m_bIsDead = *(*iter)->GetDeadState();
	CBoss::WorldMatrix();
	AStarState();
	//cout << "body X : " << m_tInfo.vPos.x << endl;
	//cout << "body Y : " << m_tInfo.vPos.y << endl;
	return 0;
}

void CBigStevenBody::Render(void)
{
	CBoss::Render();
}

void CBigStevenBody::Release(void)
{

}
void CBigStevenBody::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case BOSS_STAND:
			m_wstrStateKey = L"BigStevenBody_Walk_UD";
			m_tFrame = FRAME(2.f, 0.f, 10.f);
			break;
		case BOSS_TRACK_UD:
			m_wstrStateKey = L"BigStevenBody_Walk_UD";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BOSS_TRACK_LEFT:
			m_wstrStateKey = L"BigStevenBody_Walk_Left";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BOSS_TRACK_RIGHT:
			m_wstrStateKey = L"BigStevenBody_Walk_Right";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BOSS_TRACK_RUN_UD:
			m_wstrStateKey = L"BigStevenBody_Run_UD";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BOSS_TRACK_RUN_LEFT:
			m_wstrStateKey = L"BigStevenBody_Run_Left";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BOSS_TRACK_RUN_RIGHT:
			m_wstrStateKey = L"BigStevenBody_Run_Right";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BOSS_TIRED:
			m_wstrStateKey = L"BigStevenBody_Tired";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
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

void CBigStevenBody::AStarState(void)
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