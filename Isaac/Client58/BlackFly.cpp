#include "StdAfx.h"
#include "BlackFly.h"

CBlackFly::CBlackFly(void)
{
}

CBlackFly::~CBlackFly(void)
{
}
HRESULT CBlackFly::Initialize(void)
{
	fHp = 3.f;
	m_wstrObjKey = L"BlackFly";
	m_wstrStateKey = L"Left";
	m_dwState = MS_STAND;
	m_dwPrevState = MS_STAND;
	m_tFrame = FRAME(0.f, 100.f, 2.f);
	m_tInfo.vSize = D3DXVECTOR3(38.f,30.f,0.f);
	m_fSpeed = 0.3f;
	m_RenderType = R_WORLDOBJ;
	return S_OK;
}

int CBlackFly::Progress(void)
{
	if(m_bIsDead == true)
		return 0;
	FrameMove();
	CMonster::WorldMatrix();
	return 0;
}

void CBlackFly::Render(void)
{
	CMonster::Render();	
}

void CBlackFly::Release(void)
{
}
void CBlackFly::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case MS_STAND:
			m_wstrStateKey = L"Left";
			m_tFrame = FRAME(0.f, 100.f, 2.f);
			break;
		case MS_LEFT:
			m_wstrStateKey = L"Left";
			m_tFrame = FRAME(0.f, 100.f, 2.f);
			break;
		case MS_RIGHT:
			m_wstrStateKey = L"Right";
			m_tFrame = FRAME(0.f, 100.f, 2.f);
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