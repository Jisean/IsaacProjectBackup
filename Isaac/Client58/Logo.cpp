#include "StdAfx.h"
#include "Logo.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo(void)
:m_hThread(NULL)
{
	ZeroMemory(&m_Crt, sizeof(CRITICAL_SECTION));
}

CLogo::~CLogo(void)
{
	Release();
}

HRESULT CLogo::Initialize(void)
{
	CTextureMgr::GetInst()->InsertTexture(L"../Texture/Logo.png", L"LOGO", TEX_SINGLE);
	CTextureMgr::GetInst()->InsertTexture(L"../Texture/LoadingBar.png", L"LoadingBar1", TEX_SINGLE);
	CTextureMgr::GetInst()->InsertTexture(L"../Texture/LoadingBar2.png", L"LoadingBar2", TEX_SINGLE);

	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, LoadThread, this, 0, NULL);
	rcLDBar.left = 0;
	rcLDBar.top = 0;
	rcLDBar.right = 800;
	rcLDBar.bottom = 800;

	return S_OK;
}

int CLogo::Progress(void)
{
	rcLDBar.right = LONG(g_fLoadingCnt * 4.35);
	if(CKeyMgr::GetInst()->KeyDown(KEY_ENTER))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);

		CSceneMgr::GetInst()->SetScene(SC_STAGE);
		return 0;
	}

	return 0;
}

void CLogo::Render(void)
{
	const TEXINFO* pTexture = CTextureMgr::GetInst()->GetTexture(L"LOGO");

	if(pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	D3DXMATRIX		matWorld, matScale, matTrans;

	D3DXMatrixTranslation(&matTrans, WINCX / 2.f, WINCY / 2.f, 0.f);

	CDevice::GetInst()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInst()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixTranslation(&matTrans, 50.f, 700.f, 0.f);
	CDevice::GetInst()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInst()->GetFont()->DrawTextW(CDevice::GetInst()->GetSprite(),
		CTextureMgr::GetInst()->GetPathName().c_str(), 
		CTextureMgr::GetInst()->GetPathName().size(),
		NULL, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));



	pTexture = CTextureMgr::GetInst()->GetTexture(L"LoadingBar2");
	const TEXINFO* pTexture2 = CTextureMgr::GetInst()->GetTexture(L"LoadingBar1");

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, 500.f, 600.f, 0.f);
	matWorld = matScale * matTrans;

	CDevice::GetInst()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInst()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(pTexture->tImgInfo.Width / 2.f, 0.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));	

	
	CDevice::GetInst()->GetSprite()->Draw(pTexture2->pTexture, 
		&rcLDBar, &D3DXVECTOR3(pTexture2->tImgInfo.Width / 2.f, 0.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void CLogo::Release(void)
{
	
}

unsigned int __stdcall CLogo::LoadThread(void* pArg)
{
	CLogo*		pLogo = (CLogo*)pArg;

	EnterCriticalSection(&pLogo->GetCrt());

	if(FAILED(CTextureMgr::GetInst()->InsertTexture(L"../Texture/Tile/Tile%d.png", 
		L"TILE", TEX_MULTI, L"Tile", 27)))
	{
		ERR_MSG(L"Tile Texture Load Failed");
		return E_FAIL;
	}

	if(FAILED(CTextureMgr::GetInst()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		ERR_MSG(L"Texture Load Failed");
		return E_FAIL;
	}


	if(FAILED(CObjMgr::GetInst()->Initialize()))
	{
		ERR_MSG(L"ObjMgr Init Failed");
		return E_FAIL;
	}

	CTextureMgr::GetInst()->SetPathName(L"로딩 완료");


	LeaveCriticalSection(&pLogo->GetCrt());
	_endthreadex(0);
	return 0;
}

CRITICAL_SECTION CLogo::GetCrt(void)
{
	return m_Crt;
}
