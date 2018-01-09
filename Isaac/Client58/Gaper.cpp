#include "StdAfx.h"
#include "Gaper.h"
#include "Astar.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
CGaper::CGaper(void)
{
}

CGaper::~CGaper(void)
{
}

HRESULT CGaper::Initialize(void)
{
	fHp = 10.f;
	m_wstrObjKey = L"Gaper";
	m_wstrStateKey = L"UD";
	m_dwState = MS_STAND;
	m_dwPrevState = MS_STAND;
	m_tFrame = FRAME(2.f, 0.f, 10.f);
	m_tInfo.vSize = D3DXVECTOR3(56.f, 70.f, 0.f);
	m_fSpeed = 1.f;
	m_RenderType = R_WORLDOBJ;
	m_RoomType = 3;
	return S_OK;
}

int CGaper::Progress(void)
{
	srand((unsigned)time(NULL));
	if(m_bIsDead == true)
	{
		--g_iRoomMobCnt3;
		CSoundMgr::GetInst()->Monster2Sound(L"mobdeath2.wav");
		return 1;
	}
	
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	CMonster::WorldMatrix();
	if(*(*iter)->GetRoomType() == m_RoomType)
	{
		if(rand()%2 == 0)
		{
			if(m_dwTime + 2000 < GetTickCount())
			{
				CSoundMgr::GetInst()->Monster2Sound(L"gaperchase1.wav");
				m_dwTime = GetTickCount();
			}
		}
		else
		{
			if(m_dwTime + 3000 < GetTickCount())
			{
				CSoundMgr::GetInst()->Monster2Sound(L"gaperchase2.wav");
				m_dwTime = GetTickCount();
			}

		}
		FrameMove();
		CAStar::GetInst()->AStarStartPos(this->m_tInfo.vPos, (*iter)->GetInfo()->vPos);//스타트좌표를 계속 받아줘야한다.를 생각해보자
		CMonster::AStarMove();
	}
	AStarState();
	return 0;
}

void CGaper::Render(void)
{
	CMonster::Render();
}

void CGaper::Release(void)
{
}
void CGaper::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case MS_STAND:
			m_wstrStateKey = L"UD";
			m_tFrame = FRAME(2.f, 0.f, 10.f);
			break;
		case MS_UD:
			m_wstrStateKey = L"UD";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case MS_LEFT:
			m_wstrStateKey = L"Left";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case MS_RIGHT:
			m_wstrStateKey = L"Right";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		}
		m_dwPrevState = m_dwState;
	}

	
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(m_dwState != MS_STAND)
		{
			m_dwState = MS_STAND;
		}
		
		m_tFrame.fFrame = 0.f;
	}

}

void CGaper::AStarState(void)
{
	fPrevDirX = m_tInfo.vDir.x;
	fPrevDirY = m_tInfo.vDir.y;
	if(m_tInfo.vDir.x > 0 && (m_tInfo.vDir.y < 1.f || m_tInfo.vDir.y > -1.f || m_tInfo.vDir.y < -9999.f || m_tInfo.vDir.y > 9999.f))
	{
		m_dwState = MS_RIGHT;
	}
	else if(m_tInfo.vDir.x < 0 && (m_tInfo.vDir.y < 1.f || m_tInfo.vDir.y > -1.f || m_tInfo.vDir.y < -9999.f || m_tInfo.vDir.y > 9999.f))
	{
		m_dwState = MS_LEFT;
	}
	else if(m_tInfo.vDir.y > 0 && (m_tInfo.vDir.x < 1.f || m_tInfo.vDir.x > -1.f || m_tInfo.vDir.x < -9999.f || m_tInfo.vDir.x > 9999.f))
	{
		m_dwState = MS_UD;
	}
	else if(m_tInfo.vDir.y < 0 && (m_tInfo.vDir.x < 1.f || m_tInfo.vDir.x > -1.f || m_tInfo.vDir.x < -9999.f || m_tInfo.vDir.x > 9999.f))
	{
		m_dwState = MS_UD;
	}

	else if(fPrevDirX == m_tInfo.vDir.x && fPrevDirY == m_tInfo.vDir.y)
	{
		m_dwState = MS_STAND;
	}


}