#include "StdAfx.h"
#include "Obj.h"

D3DXVECTOR3 CObj::m_vScroll;

CObj::CObj(void)
: m_pTexture(CTextureMgr::GetInst())
, m_pDevice(CDevice::GetInst())
, m_wstrObjKey(L"")
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_dwTime = GetTickCount();
	m_RenderType = R_END;

}

CObj::~CObj(void)
{
}

void CObj::SetPos(D3DXVECTOR3 vPos)
{
	m_tInfo.vPos = vPos;
}
void CObj::SetPos(float _fX, float _fY)
{
	m_tInfo.vPos.x = _fX;
	m_tInfo.vPos.y = _fY;
}

void CObj::SetPos(D3DXVECTOR3 vPos, FIREWAY _way)
{
	m_tInfo.vPos = vPos;
	m_fireway = _way;
}

void CObj::SetPos(float _fX, float _fY, FIREWAY _way)
{
	m_tInfo.vPos.x = _fX;
	m_tInfo.vPos.y = _fY;
	m_fireway = _way;
}

void CObj::SetPos(D3DXVECTOR3 vPos, HUDTYPE _type)
{
	m_tInfo.vPos = vPos;
	m_dwState = _type;
	m_dwState2 = NULL;
}

void CObj::SetPos(D3DXVECTOR3 vPos, HUDNUMTYPE _type)
{
	m_tInfo.vPos = vPos;
	m_dwState = NULL;
	m_dwState2 = _type;
	m_dwNumState = H_0;
}

void CObj::SetPos(D3DXVECTOR3 vPos, PICKUP _type)
{
	m_tInfo.vPos = vPos;
	m_dwState = _type;
}

void CObj::SetPos(D3DXVECTOR3 vPos, PASSIVEITEM _type)
{
	m_tInfo.vPos = vPos;
	m_dwState = _type;
}
void CObj::SetPos2(float _fX, float _fY, PASSIVEITEM _type)
{
	m_tInfo.vPos.x = _fX;
	m_tInfo.vPos.y = _fY;
	m_dwState2 = _type;
}
void CObj::SetPos(float _fX, float _fY, D3DXVECTOR3 _vDir, float Angle)
{
	m_tInfo.vPos.x = _fX;
	m_tInfo.vPos.y = _fY;
	m_tInfo.vDir = _vDir;
	m_fAngle = Angle;
}
void CObj::SetPos(D3DXVECTOR3 vPos, EFFECT _type)
{
	m_tInfo.vPos = vPos;
	m_dwState = _type;
}
void CObj::SetPos(D3DXVECTOR3 vPos, BOSSHP _type)
{
	m_tInfo.vPos = vPos;
	m_dwState = _type;
}


INFO* CObj::GetInfo(void)
{
	return &m_tInfo;
}

const wstring& CObj::GetObjKey(void)
{
	return m_wstrObjKey;
} 
void CObj::SetDead()
{
	m_bIsDead = true;
}

void CObj::SetHP(float _hp)
{
	fHp += _hp;
	if(fHp > iMaxHp)
		fHp = (float)iMaxHp;
}
void CObj::SetMaxHp(int _maxhp)
{
	iMaxHp += _maxhp;
}
void CObj::SetRange(float _range)
{
	fRange += _range;
}
void CObj::SetTear(float _tear)
{
	fTears += _tear;
}
void CObj::SetSpeed(float _speed)
{
	fSpeed += _speed;
}
void CObj::SetShotSpeed(float _shotspeed)
{
	fShotSpeed += _shotspeed;
}
void CObj::SetCoin(int _coin)
{
	if(iCoins + _coin >= 99)
		iCoins = 99;
	else
		iCoins += _coin;
}
void CObj::SetKey(int _key)
{
	if(iKeys + _key >= 99)
		iKeys = 99;
	else
		iKeys += _key;
}
void CObj::SetBomb(int _bomb)
{
	if(iBombs + _bomb >= 99)
		iBombs = 99;
	else
		iBombs += _bomb;
}
void CObj::SetAtt(float _att)
{
	fAttack += _att;
}
void CObj::SetMonHp(float _hp)
{
	fHp += _hp;
	if(fHp < 0.f)
		m_bIsDead = true;
		
}