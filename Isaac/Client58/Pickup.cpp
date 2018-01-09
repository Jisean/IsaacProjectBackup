#include "StdAfx.h"
#include "Pickup.h"

CPickup::CPickup(void)
{
}

CPickup::~CPickup(void)
{
}
HRESULT CPickup::Initialize()
{
	m_bPickupLoad = false;
	m_wstrObjKey = L"Item";
	m_RenderType = R_WORLDOBJ;
	return S_OK;
}
int CPickup::Progress()
{
	if(m_bIsDead == true)
		return 1;
	if(m_bPickupLoad == false)
	{
		if(m_dwState == PICK_BATTERY)
		{
			m_wstrStateKey = L"BatteryPickup";
			m_tFrame = FRAME(0.f,0.f,1.f);
			m_dwPrevState = PICK_BATTERY;
		}
		else if(m_dwState == PICK_BOMB || m_dwState == PICK_DOUBLEBOMB)
		{
			m_wstrStateKey = L"BombPickup";
			if(m_dwState == PICK_BOMB)
			{
				m_tFrame = FRAME(0.f,0.f,2.f);
				m_dwPrevState = PICK_BOMB;
			}
			else
			{
				m_tFrame = FRAME(1.f,0.f,2.f);
				m_dwPrevState = PICK_DOUBLEBOMB;
			}
		}
		else if(m_dwState == PICK_DIME)
		{
			m_wstrStateKey = L"DimePickup";
			m_tFrame = FRAME(0.f,6.f,6.f);
			m_dwPrevState = PICK_DIME;
		}
		else if(m_dwState == PICK_HEART || m_dwState == PICK_HALFHEART || m_dwState == PICK_DOUBLEHEART)
		{
			m_wstrStateKey = L"HeartPickup";
			if(m_dwState == PICK_HEART)
			{
				m_dwPrevState = PICK_HEART;
				m_tFrame = FRAME(0.f,0.f,3.f);
			}
			else if(m_dwState == PICK_HALFHEART)
			{
				m_dwPrevState = PICK_HALFHEART;
				m_tFrame = FRAME(1.f,0.f,3.f);
			}
			else
			{
				m_dwPrevState = PICK_DOUBLEHEART;
				m_tFrame = FRAME(2.f,0.f,3.f);
			}

		}
		else if(m_dwState == PICK_KEY || m_dwState == PICK_DOUBLEKEY)
		{
			m_wstrStateKey = L"KeyPickup";
			if(m_dwState == PICK_KEY)
			{
				m_tFrame = FRAME(0.f,0.f,2.f);
				m_dwPrevState = PICK_KEY;
			}
			else
			{
				m_tFrame = FRAME(1.f,0.f,2.f);
				m_dwPrevState = PICK_DOUBLEKEY;
			}
		}
		else if(m_dwState == PICK_NICKEL)
		{
			m_wstrStateKey = L"NickelPickup";
			m_tFrame = FRAME(0.f,6.f,6.f);
			m_dwPrevState = PICK_NICKEL;
		}
		else if(m_dwState == PICK_PENNY)
		{
			m_wstrStateKey = L"PennyPickup";
			m_tFrame = FRAME(0.f,6.f,6.f);
			m_dwPrevState = PICK_PENNY;
		}
		m_bPickupLoad = true;
	}
	FrameMove();
	CItem::WorldMatrix();
	return 0;
}
void CPickup::Render()
{
	CItem::Render();
}
void CPickup::Release()
{

}
void CPickup::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case PICK_PENNY:
			m_tFrame = FRAME(0.f, 1.f, 6.f);
			break;
		case PICK_NICKEL:
			m_tFrame = FRAME(0.f, 1.f, 6.f);
			break;
		case PICK_DIME:
			m_tFrame = FRAME(0.f, 1.f, 6.f);
			break;
		case PICK_KEY:
			m_tFrame = FRAME(0.f, 0.f, 2.f);
			break;
		case PICK_DOUBLEKEY:
			m_tFrame = FRAME(1.f, 0.f, 2.f);
			break;
		case PICK_BOMB:
			m_tFrame = FRAME(0.f, 0.f, 2.f);
			break;
		case PICK_DOUBLEBOMB:
			m_tFrame = FRAME(1.f, 0.f, 2.f);
			break;
		case PICK_BATTERY:
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case PICK_HEART:
			m_tFrame = FRAME(0.f, 0.f, 3.f);
			break;
		case PICK_HALFHEART:
			m_tFrame = FRAME(1.f, 0.f, 3.f);
			break;
		case PICK_DOUBLEHEART:
			m_tFrame = FRAME(2.f, 0.f, 3.f);
			break;
		}
		m_tStartFrame = m_tFrame;
		m_dwPrevState = m_dwState;
	}

	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		
		
		m_tFrame.fFrame = 0.f;
	}


}