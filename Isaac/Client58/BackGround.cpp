#include "StdAfx.h"
#include "BackGround.h"
#include "TimeMgr.h"

CBackGround::CBackGround(void)
{
	m_DC = GetDC(g_hWnd);
}

CBackGround::~CBackGround(void)
{
	Release();
}

HRESULT CBackGround::Initialize(void)
{
	LoadTile(L"../Data/Basement.dat");

	if(FAILED(m_pTexture->InsertTexture(L"../Texture/Map/Basement_All.png", L"BASEMENT",TEX_SINGLE)))
	{
		MessageBox(g_hWnd,L"Basement Texture Load Failed",L"Basement",NULL);
		return S_FALSE;
	}

	m_fSpeed =300.f;

	m_iTileRenderX = WINCX / TILECX + 2;
	m_iTileRenderY = WINCY / TILECY + 2;

	m_RenderType = R_BACKGROUND;

	return S_OK;
}

int CBackGround::Progress(void)
{
	D3DXVECTOR3		vMouse = ::GetMouse();

	//if(0 > vMouse.x)
	//	m_vScroll.x += m_fSpeed * CTimeMgr::GetInst()->GetTime();

	//if(WINCX < vMouse.x)
	//	m_vScroll.x -= m_fSpeed * CTimeMgr::GetInst()->GetTime();

	//if(0 > vMouse.y)
	//	m_vScroll.y += m_fSpeed * CTimeMgr::GetInst()->GetTime();

	//if(WINCY < vMouse.y)
	//	m_vScroll.y -= m_fSpeed * CTimeMgr::GetInst()->GetTime();


	return 0;
}

void CBackGround::Render(void)
{
	TCHAR	szBuf[MIN_STR] = L"";

	D3DXMATRIX	matTrans;

	const TEXINFO* pTexture = m_pTexture->GetTexture(L"BASEMENT", L"Basement",NULL);

	D3DXMatrixTranslation(&matTrans, 
		pTexture->tImgInfo.Width / 2.f + m_vScroll.x, 
		pTexture->tImgInfo.Height / 2.f + m_vScroll.y, 0.f);

	m_pDevice->GetSprite()->SetTransform(&matTrans);

	m_pDevice->GetSprite()->Draw(pTexture->pTexture,NULL, &D3DXVECTOR3(
		pTexture->tImgInfo.Width  / 2.f, 
		pTexture->tImgInfo.Height / 2.f,
		0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	for(int i = 0; i < m_iTileRenderY; ++i)
	{
		for(int j = 0; j < m_iTileRenderX; ++j)
		{
			int iCullX = int(-m_vScroll.x) / TILECX;
			int iCullY = int(-m_vScroll.y) / TILECY;

			int INDEX = (i + iCullY) * TILEX + (j + iCullX);

			if(INDEX < 0 || INDEX >= TILEX * TILEY)
				continue;

			const TEXINFO* pTexture = m_pTexture->GetTexture(L"TILE", L"Tile", 
				m_vecTile[INDEX]->byDrawID);

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[INDEX]->vPos.x + m_vScroll.x, 
				m_vecTile[INDEX]->vPos.y + m_vScroll.y, 0.f);

			m_pDevice->GetSprite()->SetTransform(&matTrans);

			m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
				NULL, &D3DXVECTOR3(TILECX/2, TILECY/2, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

			// 폰트 함수
			/*wsprintf(szBuf, L"%d", INDEX);
			m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), 
				szBuf, lstrlen(szBuf), NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));*/
		}
	}
}

void CBackGround::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DELETEOBJ());
	m_vecTile.clear();
}

void CBackGround::LoadTile(const wstring& wstrPath)
{
	HANDLE	hFile = CreateFile(wstrPath.c_str(), GENERIC_READ, 
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte;

	while(true)
	{
		TILE*		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);		
	}

	CloseHandle(hFile);
}

const vector<TILE*>* CBackGround::GetTile(void)
{
	return &m_vecTile;
}
