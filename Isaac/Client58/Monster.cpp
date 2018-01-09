#include "StdAfx.h"
#include "Monster.h"
#include "Astar.h"
#include "ObjMgr.h"

CMonster::CMonster(void)
{
}

CMonster::~CMonster(void)
{
}
HRESULT CMonster::Initialize(void)
{
	m_bIsDead = false;
	m_RenderType = R_WORLDOBJ;
	return S_OK;
}

int CMonster::Progress(void)
{
	return 0;
}

void CMonster::Render(void)
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
void CMonster::Release(void)
{
}
void CMonster::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}

void CMonster::AStarMove(void)
{
	list<int>* pBestList = CAStar::GetInst()->GetBestList();

	if(pBestList->empty())
		return;

	const vector<TILE*>*	pVecTile = CObjMgr::GetInst()->GetTile();

	if(pVecTile == NULL)
		return;

	int iMoveIndex = pBestList->front();

	m_tInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - m_tInfo.vPos;

	//cout << "Dir x : " << m_tInfo.vDir.x << endl;
	//cout << "Dir y : " << m_tInfo.vDir.y << endl;

	float fDistance = D3DXVec3Length(&m_tInfo.vDir);

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	if(fDistance < 5.f)
	{
		pBestList->pop_front();
	}
}
