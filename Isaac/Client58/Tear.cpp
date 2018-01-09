#include "StdAfx.h"
#include "Tear.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Effect.h"
#include "SoundMgr.h"
CTear::CTear(void)
{
}

CTear::~CTear(void)
{
}

HRESULT CTear::Initialize(void)
{
	m_wstrObjKey = L"Tear";
	m_wstrStateKey = L"Normal";//나중에 if문으로 눈물상태 변경할것
	m_tFrame = FRAME(5.f, 0.f, 5.f);
	m_tInfo.vSize = D3DXVECTOR3(24.f,24.f,0.f);
	m_bIsDead = false;
	m_RenderType = R_WORLDOBJ_TEAR;
	return S_OK;
}

int CTear::Progress(void)
{
	if(m_bIsDead == true)
	{
		CSoundMgr::GetInst()->EffectSound1(L"tearhit.wav");
		CObjMgr::GetInst()->AddObj(OBJ_EFFECT, CObjFactory<CEffect>::CreateObj(m_tInfo.vPos,EF_TEARSPLASH));
		return 1;
	}
	//공격력에따라 눈물크기 변경되게할것

	if(m_fireway == WAY_UP)
	{
		m_tInfo.vPos.y -= 5.f;
	}
	if(m_fireway == WAY_DOWN)
	{
		m_tInfo.vPos.y += 5.f;
	}
	if(m_fireway == WAY_LEFT)
	{
		m_tInfo.vPos.x -= 5.f;
	}
	if(m_fireway == WAY_RIGHT)
	{
		m_tInfo.vPos.x += 5.f;
	}

	//꺽이는거 콤바인써서 해결볼것

	WorldMatrix();

	return 0;
}
void CTear::Render(void)
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

void CTear::Release(void)
{
}
void CTear::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}
