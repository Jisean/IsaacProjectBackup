#include "StdAfx.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Effect.h"
CBullet::CBullet(void)
{
}

CBullet::~CBullet(void)
{
}

HRESULT CBullet::Initialize(void)
{
	m_wstrObjKey = L"Bullet";
	m_wstrStateKey = L"Normal";
	m_tFrame = FRAME(0.f, 0.f, 1.f);
	m_bIsDead = false;
	m_fAngle = 0.f;
	m_tInfo.vSize = D3DXVECTOR3(26.f,26.f,0.f);
	m_RenderType = R_WORLDOBJ_TEAR;
	return S_OK;
}

int CBullet::Progress(void)
{
	if(m_bIsDead == true)
	{
		CObjMgr::GetInst()->AddObj(OBJ_EFFECT, CObjFactory<CEffect>::CreateObj(m_tInfo.vPos,EF_BULLETSPLASH));
		return 1;
	}

	InnerProduct();
	WorldMatrix();

	if(m_tInfo.vPos.x + m_vScroll.x > WINCX || m_tInfo.vPos.y + m_vScroll.y > WINCY || m_tInfo.vPos.x + m_vScroll.x < 0.f || m_tInfo.vPos.y + m_vScroll.y < 0.f)
		return 1;

		
	

	return 0;
}
void CBullet::Render(void)
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

void CBullet::Release(void)
{
}
void CBullet::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}

void CBullet::InnerProduct(void)
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();

	D3DXVec3Normalize(&m_tInfo.vDir,&m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	m_fAngle = D3DXVec3Dot(&m_tInfo.vDir,&m_tInfo.vLook);
	m_fAngle = m_fAngle * 3.1415962f / 180;

	m_tInfo.vPos.y += m_tInfo.vDir.y * 5.f;
	m_tInfo.vPos.x += (m_tInfo.vDir.x + m_fAngle) * 5.f; 

}