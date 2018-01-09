#include "StdAfx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "Stage.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr(void)
: m_pScene(NULL)
{
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::SetScene(SCENEID _eScene)
{
	if(m_pScene)
		::Safe_Delete(m_pScene);

	switch(_eScene)
	{
	case SC_LOGO:
		m_pScene = new CLogo;
		break;

	case SC_STAGE:
		m_pScene = new CStage;
		break;
	}

	if(FAILED(m_pScene->Initialize()))
	{
		ERR_MSG(L"Scene Init Failed");
		return;
	}
	if(FAILED(m_pScene->Progress()))
	{
		ERR_MSG(L"Scene Progress Failed");
		return;
	}
}

void CSceneMgr::Progress(void)
{
	int iResult = 0;

	if(m_pScene)
		iResult = m_pScene->Progress();
}

void CSceneMgr::Render(void)
{
	if(m_pScene)
		m_pScene->Render();

}

void CSceneMgr::Release(void)
{
	::Safe_Delete(m_pScene);
}
