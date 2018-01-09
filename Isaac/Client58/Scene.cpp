#include "StdAfx.h"
#include "Scene.h"

float	g_fLoadingCnt = 0.f;
int	g_iBossTotalHp = 80;

CScene::CScene(void)
: m_pObjMgr(CObjMgr::GetInst())
{
}

CScene::~CScene(void)
{
}
