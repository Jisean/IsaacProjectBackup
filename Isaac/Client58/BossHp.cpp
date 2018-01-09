#include "StdAfx.h"
#include "BossHp.h"

CBossHp::CBossHp(void)
{
}

CBossHp::~CBossHp(void)
{
}
HRESULT	CBossHp::Initialize()
{
	m_wstrObjKey = L"UI";
	m_wstrStateKey = L"BossHp";
	m_bIsBossRoom = false;
	m_bHasUI = false;
	rcHpBar.left = 0;
	rcHpBar.top = 0;
	rcHpBar.right = 800;
	rcHpBar.bottom = 800;
	if(m_dwState == BH_UNDER)
	{
		m_RenderType = R_UI;
	}
	else if(m_dwState == BH_OVER)
	{
		m_RenderType = R_UI_BOSSHP;
	}
	else
		m_RenderType = R_UI;
	return S_OK;
}

int CBossHp::Progress()
{
	rcHpBar.right = LONG(g_iBossTotalHp * 3.3f);
	FrameMove();
	WorldMatrix();
	return 0;
}

void CBossHp::Render()
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if(pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	if(m_dwState == BH_UNDER)
	{
	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if(m_dwState == BH_OVER)
	{
		m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
		&rcHpBar, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CBossHp::Release()
{
}
void CBossHp::FrameMove(void)
{
	switch(m_dwState)
	{
	case BH_UNDER:
		m_tFrame = FRAME(1.f, 0.f, 1.f);
		break;
	case BH_OVER:
		m_tFrame = FRAME(0.f, 0.f, 1.f);
		break;
	}

}
void CBossHp::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x, 
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;
}