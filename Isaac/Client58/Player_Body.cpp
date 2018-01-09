#include "StdAfx.h"
#include "Player_Body.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"

CPlayer_Body::CPlayer_Body(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CPlayer_Body::~CPlayer_Body(void)
{
	Release();
}

HRESULT CPlayer_Body::Initialize(void)
{
	m_wstrObjKey = L"Player";
	m_wstrStateKey = L"Body_UD";
	m_dwState = BODY_STAND;
	m_dwPrevState = BODY_STAND;
	m_tFrame = FRAME(2.f, 0.f, 10.f);
	m_RenderType = R_WORLDOBJ_BODY;
	return S_OK;
}

int CPlayer_Body::Progress(void)
{

	FrameMove();
	list<CObj*>::iterator iter = pObjList[OBJ_PLAYER].begin();
	m_tInfo.vPos = (*iter)->GetInfo()->vPos;
	bInvincible = *(*iter)->GetInvincible();
	StateKeyInput();
	CPlayer::WorldMatrix();
	if(bInvincible == true)
	{
		if(m_dwTime + 3000 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}
	//cout << "body X : " << m_tInfo.vPos.x << endl;
	//cout << "body Y : " << m_tInfo.vPos.y << endl;
	return 0;
}

void CPlayer_Body::Render(void)
{
	CPlayer::Render();
}

void CPlayer_Body::Release(void)
{

}
void CPlayer_Body::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case BODY_STAND:
			m_wstrStateKey = L"Body_UD";
			m_tFrame = FRAME(2.f, 0.f, 10.f);
			break;
		case BODY_UD:
			m_wstrStateKey = L"Body_UD";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BODY_LEFT:
			m_wstrStateKey = L"Body_Left";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case BODY_RIGHT:
			m_wstrStateKey = L"Body_Right";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		}
		m_dwPrevState = m_dwState;
	}

	
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(m_dwState != BODY_STAND)
		{
			m_dwState = BODY_STAND;
		}
		
		m_tFrame.fFrame = 0.f;
	}

}
void CPlayer_Body::StateKeyInput(void)
{
	if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
	{
		m_dwState = BODY_UD;
	}

	else if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
	{
		m_dwState = BODY_UD;
	}

	else if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
	{
		m_dwState = BODY_LEFT;
	}

	else if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
	{
		m_dwState = BODY_RIGHT;
	}
	else
	{
		m_dwState = BODY_STAND;
	}
}




