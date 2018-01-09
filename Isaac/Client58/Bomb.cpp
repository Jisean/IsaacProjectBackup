#include "StdAfx.h"
#include "Bomb.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Effect.h"
#include "SoundMgr.h"

CBomb::CBomb(void)
{
}

CBomb::~CBomb(void)
{
}
HRESULT CBomb::Initialize(void)
{
	m_wstrObjKey = L"Bomb";
	m_wstrStateKey = L"Normal";
	m_dwState = B_INSTALL;
	m_tFrame = FRAME(0.f, 0.f, 12.f);
	m_bIsDead = false;
	m_RenderType = R_WORLDOBJ;
	return S_OK;
}

int CBomb::Progress(void)
{	
	if(m_bIsDead == true)
	{
		CSoundMgr::GetInst()->EffectSound1(L"explosion1.wav");
		CObjMgr::GetInst()->AddObj(OBJ_EFFECT_EXPLOSION, CObjFactory<CEffect>::CreateObj(m_tInfo.vPos,EF_EXPLOSION));
		return 1;
	}

	if(m_dwTime + 500 < GetTickCount())
	{
		m_dwState = B_BLAST;
	}
	
	WorldMatrix();
	FrameMove();
	return 0;
}
void CBomb::Render(void)
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

void CBomb::Release(void)
{
}
void CBomb::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}

void CBomb::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case B_INSTALL:
			m_tFrame = FRAME(0.f, 0.f, 12.f);
			break;
		case EF_BULLETSPLASH:
			m_tFrame = FRAME(0.f, 20.f, 12.f);
			break;
		}
		m_dwPrevState = m_dwState;
	}

	
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		/*if(m_dwState != B_INSTALL)
		{
			m_dwState = B_INSTALL;
		}*/
		
		m_tFrame.fFrame = m_tFrame.fMax -1;
		m_bIsDead = true;
	}

}