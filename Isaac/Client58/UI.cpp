#include "StdAfx.h"
#include "UI.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "HpUI.h"
#include "Minimap.h"
#include "PickupUI.h"
#include "BossHp.h"

CUI::CUI(void)
{
}

CUI::~CUI(void)
{
}

HRESULT	CUI::Initialize()
{
	m_bIsBossRoom = false;
	m_bIsDelete = false;
	m_bHasUI = false;
	m_RenderType = R_UI;
	return S_OK;
}

int CUI::Progress()
{
	if(m_bHasUI == false)
	{
		////////////////////////////////////////HPBAR/////////////////////////////////////////////
		list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
		m_iCount = *(*iter)->GetPlayerMaxHP();

		for(int i = 0; i < m_iCount; ++i)
		{
			CObjMgr::GetInst()->AddObj(OBJ_UI_HP,
				CObjFactory<CHpUI>::CreateObj(100.f + i * 22 ,50.f));
		}

		//////////////////////////////////////////////////////////////////////////////////////////
		/*
		CObjMgr::GetInst()->AddObj(OBJ_UI_MINIMAP,
			CObjFactory<CMinimap>::CreateObj(700.f,50.f));*/
		///////////////////////////////////////HUD_ICON///////////////////////////////////////////
		CObjMgr::GetInst()->AddObj(OBJ_UI_HUD,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(50.f,100.f,0.f),HUD_COIN));
		CObjMgr::GetInst()->AddObj(OBJ_UI_HUD,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(50.f,120.f,0.f),HUD_BOMB));
		CObjMgr::GetInst()->AddObj(OBJ_UI_HUD,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(50.f,140.f,0.f),HUD_KEY));
		////////////////////////////////////////HUD_NUM///////////////////////////////////////////
		CObjMgr::GetInst()->AddObj(OBJ_UI_COIN_NUM1,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(64.f,100.f,0.f),HN_COIN));
		CObjMgr::GetInst()->AddObj(OBJ_UI_COIN_NUM2,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(74.f,100.f,0.f),HN_COIN));

		CObjMgr::GetInst()->AddObj(OBJ_UI_BOMB_NUM1,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(64.f,120.f,0.f),HN_COIN));
		CObjMgr::GetInst()->AddObj(OBJ_UI_BOMB_NUM2,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(74.f,120.f,0.f),HN_COIN));

		CObjMgr::GetInst()->AddObj(OBJ_UI_KEY_NUM1,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(64.f,140.f,0.f),HN_KEY));
		CObjMgr::GetInst()->AddObj(OBJ_UI_KEY_NUM2,
			CObjFactory<CPickupUI>::CreateObj(D3DXVECTOR3(74.f,140.f,0.f),HN_KEY));

		////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////
		m_bHasUI = true;
	}

	if(*(CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].front()->GetRoomType()) == 5 && g_iRoomMobCntBoss !=0 && m_bIsBossRoom == false)
	{
		CObjMgr::GetInst()->AddObj(OBJ_UI_BOSSHP_UNDER,
			CObjFactory<CBossHp>::CreateObj(D3DXVECTOR3(WINCX/2.f,100.f,0.f),BH_UNDER));
		CObjMgr::GetInst()->AddObj(OBJ_UI_BOSSHP_OVER,
			CObjFactory<CBossHp>::CreateObj(D3DXVECTOR3(WINCX/2.f,100.f,0.f),BH_OVER));
		m_bIsBossRoom = true;
	}

	if(g_iRoomMobCntBoss == 0 && m_bIsDelete == false && m_bIsBossRoom == true)
	{
		CObjMgr::GetInst()->GetObjList()[OBJ_UI_BOSSHP_UNDER].clear();
		CObjMgr::GetInst()->GetObjList()[OBJ_UI_BOSSHP_OVER].clear();
		m_bIsDelete = true;
	}
	WorldMatrix();
	return 0;
}

void CUI::Render()
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if(pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUI::Release()
{
}
void CUI::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x, 
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;
}
