#include "StdAfx.h"
#include "Obj.h"
#include "Device.h"

CObj::CObj(void)
: m_pDevice(CDevice::GetInst())
, m_pTexture(CTextureMgr::GetInst())
{
}

CObj::~CObj(void)
{
}

void CObj::SetPos(D3DXVECTOR3& vPos)
{
	m_tInfo.vPos = vPos;
}

void CObj::SetPos(float _fX, float _fY)
{
	m_tInfo.vPos.x = _fX;
	m_tInfo.vPos.y = _fY;
}
