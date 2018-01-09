#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect(void)
{
}

CEffect::~CEffect(void)
{
}
HRESULT CEffect::Initialize(void)
{
	m_wstrObjKey = L"Effect";
	m_bIsDead = false;
	m_RenderType = R_WORLDOBJ_TEAR;
	m_bEffectLoad = false;
	return S_OK;
}

int CEffect::Progress(void)
{	
	if(m_bIsDead == true)
	{
		return 1;
	}
	if(m_bEffectLoad == false)
	{
		if(m_dwState == EF_TEARSPLASH)
		{
			m_wstrStateKey = L"TearSplash";
			m_tFrame = FRAME(0.f, 20.f, 15.f);
		}
		else if(m_dwState == EF_BULLETSPLASH)
		{
			m_wstrStateKey = L"BulletSplash";
			m_tFrame = FRAME(0.f, 20.f, 15.f);
		}
		else if(m_dwState == EF_EXPLOSION)
		{
			m_wstrStateKey = L"Explosion";
			m_tInfo.vSize = D3DXVECTOR3(166.f,174.f,0.f);
			m_tFrame = FRAME(0.f, 20.f, 11.f);
		}
		m_bEffectLoad = true;
	}

	WorldMatrix();
	FrameMove();
	return 0;
}
void CEffect::Render(void)
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if(pTexture == NULL)
		return;

	if(m_dwState != EF_EXPLOSION)
	{
		float	fX = pTexture->tImgInfo.Width / 2.f;
		float	fY = pTexture->tImgInfo.Height / 2.f;

		m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		float	fX = pTexture->tImgInfo.Width / 2.f;
		float	fY = pTexture->tImgInfo.Height - 20.f;

		m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CEffect::Release(void)
{
}
void CEffect::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}

void CEffect::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case EF_TEARSPLASH:
			m_tFrame = FRAME(0.f, 20.f, 15.f);
			break;
		case EF_BULLETSPLASH:
			m_tFrame = FRAME(0.f, 20.f, 15.f);
			break;
		case EF_EXPLOSION:
			m_tFrame = FRAME(0.f, 20.f, 11.f);
			break;
		}
		m_dwPrevState = m_dwState;
	}


	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		/*if(m_dwState != EF_TEARSPLASH)
		{
		m_dwState = EF_TEARSPLASH;
		}
		*/
		m_tFrame.fFrame = m_tFrame.fMax -1;
		m_bIsDead = true;
	}

}
