#include "StdAfx.h"
#include "MainGame.h"
#include "Device.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "AStar.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame(void)
:m_pDevice(CDevice::GetInst())
, m_pScene(CSceneMgr::GetInst())
, m_fTime(0.f)
, m_iCount(0)
{
	//ZeroMemory(m_szFPS, sizeof(m_szFPS));
	CSoundMgr::GetInst()->Initialize();
	CSoundMgr::GetInst()->LoadSoundFile();
}

CMainGame::~CMainGame(void)
{
	FreeConsole();
	Release();
}

HRESULT CMainGame::Initialize(void)
{

	//AllocConsole( );                 // Allocate console window
	//freopen("CONOUT$", "a", stderr); // Redirect stderr to console
	//freopen("CONOUT$", "a", stdout); // Redirect stdout also
	//freopen("CONIN$", "r", stdin);


	if(FAILED(m_pDevice->InitDevice()))
	{
		ERR_MSG(L"Device Init Failed");
		return E_FAIL;
	}
	
	m_pScene->SetScene(SC_LOGO);

	CTimeMgr::GetInst()->InitTime();

	return S_OK;
}

void CMainGame::Progress(void)
{
	CKeyMgr::GetInst()->KeyCheck();
	CTimeMgr::GetInst()->SetTime();

	m_pScene->Progress();

	D3DXMatrixTranslation(&m_matTrans, 600.f, 50.f, 0.f);

}

void CMainGame::Render(void)
{
	++m_iCount;

	m_fTime += CTimeMgr::GetInst()->GetTime();

	if(m_fTime > 1.f)
	{
		m_fTime = 0.f;
		wsprintf(m_szFPS, L"FPS : %d", m_iCount);
		m_iCount = 0;
	}

	m_pDevice->GetDevice()->Clear(0, NULL, 
		D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->Render_Begin();

	m_pScene->Render();

	m_pDevice->GetSprite()->SetTransform(&m_matTrans);
	m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), m_szFPS, lstrlen(m_szFPS), 
		NULL, NULL, D3DCOLOR_ARGB(255, 255, 0, 0));

	m_pDevice->Render_End();
	m_pDevice->GetDevice()->Present(NULL, NULL, g_hWnd, NULL);
}

void CMainGame::Release(void)
{
	CSoundMgr::GetInst()->DestroyInst();
	CKeyMgr::GetInst()->DestroyInst();
	CAStar::GetInst()->DestroyInst();
	CTimeMgr::GetInst()->DestroyInst();
	CTextureMgr::GetInst()->DestroyInst();
	CObjMgr::GetInst()->DestroyInst();
	m_pScene->DestroyInst();
	m_pDevice->DestroyInst();
}

