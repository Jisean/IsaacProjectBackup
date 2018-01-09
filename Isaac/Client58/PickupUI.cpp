#include "StdAfx.h"
#include "PickupUI.h"
#include "Objmgr.h"

CPickupUI::CPickupUI(void)
{
}

CPickupUI::~CPickupUI(void)
{
}
HRESULT	CPickupUI::Initialize()
{
	m_wstrObjKey = L"UI";
	m_bUILoad = false;
	m_RenderType = R_UI;
	return S_OK;
}

int CPickupUI::Progress()
{
	if(m_bUILoad == false)
	{
		if((m_dwState == HUD_COIN || m_dwState == HUD_KEY || m_dwState == HUD_BOMB) && m_dwState2 == NULL)
		{
			m_wstrStateKey = L"HUD_Icon";
			m_tFrame = FRAME(0.f,0.f,3.f);
		}
		else if((m_dwState2 == HN_COIN || m_dwState2 == HN_KEY || m_dwState2 == HN_KEY) && m_dwState == NULL)
		{
			m_wstrStateKey = L"HUD_Num";
			m_tFrame = FRAME(0.f,0.f,10.f);
		}
		m_bUILoad = true;
	}
	FrameMove();
	CUI::WorldMatrix();
	CoinHud();
	BombHud();
	KeyHud();


	return 0;
}

void CPickupUI::Render()
{
	CUI::Render();
}

void CPickupUI::Release()
{

}
void CPickupUI::FrameMove(void)
{
	switch(m_dwState)
	{
	case HUD_COIN:
		m_tFrame = FRAME(0.f, 0.f, 3.f);
		break;
	case HUD_KEY:
		m_tFrame = FRAME(1.f, 0.f, 3.f);
		break;
	case HUD_BOMB:
		m_tFrame = FRAME(2.f, 0.f, 3.f);
		break;
	}

}

void CPickupUI::CoinHud()
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();

	m_iCoin = (*(*iter)->GetCoin());

	list<CObj*>::iterator secondnumiter = CObjMgr::GetInst()->GetObjList()[OBJ_UI_COIN_NUM2].begin();
	list<CObj*>::iterator firstnumiter = CObjMgr::GetInst()->GetObjList()[OBJ_UI_COIN_NUM1].begin();


	(*secondnumiter)->SetFrame(FRAME(float(m_iCoin % 10),0.f,10.f));
	(*firstnumiter)->SetFrame(FRAME(float(m_iCoin / 10),0.f,10.f));
}

void CPickupUI::KeyHud()
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();

	m_iKey = (*(*iter)->GetKey());

	list<CObj*>::iterator secondnumiter = CObjMgr::GetInst()->GetObjList()[OBJ_UI_KEY_NUM2].begin();
	list<CObj*>::iterator firstnumiter = CObjMgr::GetInst()->GetObjList()[OBJ_UI_KEY_NUM1].begin();


	(*secondnumiter)->SetFrame(FRAME(float(m_iKey % 10),0.f,10.f));
	(*firstnumiter)->SetFrame(FRAME(float(m_iKey / 10),0.f,10.f));
}

void CPickupUI::BombHud()
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();

	m_iBomb = (*(*iter)->GetBomb());

	list<CObj*>::iterator secondnumiter = CObjMgr::GetInst()->GetObjList()[OBJ_UI_BOMB_NUM2].begin();
	list<CObj*>::iterator firstnumiter = CObjMgr::GetInst()->GetObjList()[OBJ_UI_BOMB_NUM1].begin();


	(*secondnumiter)->SetFrame(FRAME(float(m_iBomb % 10),0.f,10.f));
	(*firstnumiter)->SetFrame(FRAME(float(m_iBomb / 10),0.f,10.f));
}