#include "StdAfx.h"
#include "Back.h"
#include "Tool58View.h"
#include "MapTool.h"

CBack::CBack(void)
: m_pMainView(NULL)
, m_pMapTool(NULL)
{
}

CBack::~CBack(void)
{
	Release();
}

HRESULT CBack::Initialize(void)
{
	for(int i = 0; i < TILEY; ++i)
	{
		for(int j = 0; j < TILEX; ++j)
		{
			TILE*		pTile = new TILE;

			float fX = j * float(TILECX) + float(TILECX)/4 - 20;
			float fY = i * float(TILECY) + float(TILECY)/2;

			pTile->vPos		= D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize	= D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byOption = 1;
			pTile->byDrawID = 1;
			
			m_vecTile.push_back(pTile);
		}
	}


	return S_OK;
}

int CBack::Progress(void)
{
	return 0;
}

void CBack::Render(void)
{

	D3DXMATRIX	matTrans;

		const TEXINFO* pTexture = m_pTexture->GetTexture(L"BASEMENT", L"Basement",NULL);

	D3DXMatrixTranslation(&matTrans, 
		pTexture->tImgInfo.Width / 2.f - m_pMainView->GetScrollPos(0), 
		pTexture->tImgInfo.Height / 2.f - m_pMainView->GetScrollPos(1), 0.f);
	
	m_pDevice->GetSprite()->SetTransform(&matTrans);

	m_pDevice->GetSprite()->Draw(pTexture->pTexture,NULL, &D3DXVECTOR3(
		pTexture->tImgInfo.Width  / 2.f, 
		pTexture->tImgInfo.Height / 2.f,
		0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	////////////////뒷배경


	TCHAR	szBuf[MIN_STR] = L"";

	for(int i = 0; i < TILEY; ++i)
	{
		for(int j = 0; j < TILEX; ++j)
		{
			int INDEX = i * TILEX + j;

			const TEXINFO* pTexture = m_pTexture->GetTexture(L"TILE", L"Tile", 
				m_vecTile[INDEX]->byDrawID);
			
			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[INDEX]->vPos.x - m_pMainView->GetScrollPos(0), 
				m_vecTile[INDEX]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);

			m_pDevice->GetSprite()->SetTransform(&matTrans);

			m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(TILECX /2, TILECY/2, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

			// 폰트 함수
			wsprintf(szBuf, L"%d", INDEX);
			m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), 
				szBuf, lstrlen(szBuf), NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			
		}
	}
}

void CBack::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DELETEOBJ());
	m_vecTile.clear();

}

int CBack::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if(Picking(vPos, i))
		{
			return i;
		}
	}

	return -1;
}

void CBack::TileChange(const D3DXVECTOR3& vPos, const int& iDrawID)
{
	int		iIndex = GetTileIndex(vPos);

	if(iIndex == -1)
		return;

	int iOption = CMapTool::m_iState;

	m_vecTile[iIndex]->byDrawID = iDrawID;
	m_vecTile[iIndex]->byOption = iOption;
}

bool CBack::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	D3DXVECTOR3		vPoint[4] = 
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX/2, m_vecTile[iIndex]->vPos.y - TILECY/2, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX/2, m_vecTile[iIndex]->vPos.y - TILECY/2, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX/2, m_vecTile[iIndex]->vPos.y + TILECY/2, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX/2, m_vecTile[iIndex]->vPos.y + TILECY/2, 0.f),
	};

	


	D3DXVECTOR3		vDirection[4] = 
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3		vNormal[4] = 
	{
		D3DXVECTOR3(vDirection[0].y, -vDirection[0].x, 0.f),
		D3DXVECTOR3(vDirection[1].y, -vDirection[1].x, 0.f),
		D3DXVECTOR3(vDirection[2].y, -vDirection[2].x, 0.f),
		D3DXVECTOR3(vDirection[3].y, -vDirection[3].x, 0.f)
	};

	// 법선 벡터 정규화
	for(int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for(int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3		vDestDir = vPos - vPoint[i];

		float fDot = D3DXVec3Dot(&vDestDir,&vNormal[i]);

		if(fDot > 0.f)
			return false;
	}

	return true;


	/*float		fGradient = (TILECY / 2.f ) / (TILECX / 2.f);

	D3DXVECTOR3		vPoint[4] = 
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY / 2.f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY / 2.f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f),
	}; 

	// Y = AX + B -> B = Y - AX

	float	fB[4] = 
	{
		vPoint[0].y - fGradient * vPoint[0].x,
		vPoint[1].y + fGradient * vPoint[1].x,
		vPoint[2].y - fGradient * vPoint[2].x,
		vPoint[3].y + fGradient * vPoint[3].x
	};

	// y = ax + b
	// y - ax - b == 0 직선 상
	// y - ax - b > 0 직선 위	(0, 3)
	// y - ax - b < 0 직선 아래 (1, 2)

	if(vPos.y - fGradient * vPos.x - fB[0] >= 0 &&
		vPos.y + fGradient * vPos.x - fB[1] < 0 &&
		vPos.y - fGradient * vPos.x - fB[2] < 0 &&
		vPos.y + fGradient * vPos.x - fB[3] >= 0 )
	{
		return true;
	}


	return false;*/
}

void CBack::SetMainView(CTool58View* pMainView)
{
	m_pMainView = pMainView;
}

void CBack::MiniViewRender(void)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	const TEXINFO* pTexture = m_pTexture->GetTexture(L"BASEMENT", L"Basement",NULL);

	D3DXMatrixScaling(&matScale, 0.4f, 0.4f, 0.f);

	D3DXMatrixTranslation(&matTrans, 
				pTexture->tImgInfo.Width / 4.f - m_pMainView->GetScrollPos(0) / 4.f, 
				pTexture->tImgInfo.Height / 4.f - m_pMainView->GetScrollPos(1) / 4.f, 0.f);

	matWorld = matScale * matTrans;
	
	m_pDevice->GetSprite()->SetTransform(&matWorld);

	m_pDevice->GetSprite()->Draw(pTexture->pTexture,NULL, &D3DXVECTOR3(
		pTexture->tImgInfo.Width  / 1.6f, 
		pTexture->tImgInfo.Height / 1.6f,
		0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	for(int i = 0; i < TILEY; ++i)
	{
		for(int j = 0; j < TILEX; ++j)
		{
			int INDEX = i * TILEX + j;

			const TEXINFO* pTexture = m_pTexture->GetTexture(L"TILE", L"Tile", 
				m_vecTile[INDEX]->byDrawID);

			D3DXMatrixScaling(&matScale, 0.4f, 0.4f, 0.f);

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[INDEX]->vPos.x * 0.4f - m_pMainView->GetScrollPos(0) / 4.f, 
				m_vecTile[INDEX]->vPos.y * 0.4f - m_pMainView->GetScrollPos(1) / 4.f, 0.f);

			matWorld = matScale * matTrans;

			m_pDevice->GetSprite()->SetTransform(&matWorld);

			m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(TILECX / 2.f, TILECY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
}

const vector<TILE*>* CBack::GetTile(void)
{
	return &m_vecTile;
}
