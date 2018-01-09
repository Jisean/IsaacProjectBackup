#include "StdAfx.h"
#include "AttackFly.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
CAttackFly::CAttackFly(void)
{
}

CAttackFly::~CAttackFly(void)
{
}
HRESULT CAttackFly::Initialize(void)
{
	fHp = 3.f;
	m_wstrObjKey = L"AttackFly";
	m_wstrStateKey = L"Left";
	m_dwState = MS_STAND;
	m_dwPrevState = MS_STAND;
	m_tFrame = FRAME(0.f, 100.f, 5.f);
	m_tInfo.vSize = D3DXVECTOR3(38.f,30.f,0.f);
	m_fSpeed = 0.7f;
	m_RenderType = R_WORLDOBJ;
	m_RoomType = 2;
	return S_OK;
}

int CAttackFly::Progress(void)
{
	if(m_bIsDead == true)
	{
		CSoundMgr::GetInst()->Monster2Sound(L"mobdeath3.wav");
		--g_iRoomMobCnt2;
		return 1;
	}
	
	CMonster::WorldMatrix();
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	if(*(*iter)->GetRoomType() == m_RoomType)
	{
		FrameMove();
		Tracking();
		if(m_dwTime + 200 < GetTickCount())
		{
			CSoundMgr::GetInst()->Monster1Sound(L"insectswarm.wav");
			m_dwTime = GetTickCount();
		}
	}
	else
		m_dwState = MS_STAND;
	return 0;
}

void CAttackFly::Render(void)
{
	CMonster::Render();	
}

void CAttackFly::Release(void)
{
}
void CAttackFly::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case MS_STAND:
			m_wstrStateKey = L"Left";
			m_tFrame = FRAME(0.f, 100.f, 5.f);
			break;
		case MS_LEFT:
			m_wstrStateKey = L"Left";
			m_tFrame = FRAME(0.f, 100.f, 5.f);
			break;
		case MS_RIGHT:
			m_wstrStateKey = L"Right";
			m_tFrame = FRAME(0.f, 100.f, 5.f);
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

void CAttackFly::Tracking(void)
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	m_tInfo.vDir = (*iter)->GetInfo()->vPos - m_tInfo.vPos;

	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	if(m_tInfo.vDir.x < 0)
	{
		m_dwState = MS_LEFT;
	}
	else if(m_tInfo.vDir.x > 0)
	{
		m_dwState = MS_RIGHT;
	}
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
}