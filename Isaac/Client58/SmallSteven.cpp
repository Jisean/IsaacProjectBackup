#include "StdAfx.h"
#include "SmallSteven.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Bullet.h"
#include "SoundMgr.h"

CSmallSteven::CSmallSteven(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CSmallSteven::~CSmallSteven(void)
{
}
HRESULT CSmallSteven::Initialize(void)
{
	fHp = 40.f;
	iMaxHp = 40;
	m_wstrObjKey = L"Boss";
	m_wstrStateKey = L"SmallSteaven_Normal_Left";
	m_dwState = BOSS_STAND;
	m_dwPrevState = BOSS_STAND;
	m_tFrame = FRAME(0.f, 0.f, 3.f);
	m_tInfo.vSize = D3DXVECTOR3(44.f,50.f,0.f);
	m_fSpeed = 1.f;
	m_RenderType = R_WORLDOBJ;
	m_RoomType = 5;
	m_bCooldown = false;
	m_attacksound = false;
	bInvincible = false;
	return S_OK;
}

int CSmallSteven::Progress(void)
{
	list<CObj*>::iterator bossiter = pObjList[OBJ_BOSS_BIG].begin();
	if(m_bIsDead == true)
	{
		--g_iRoomMobCntBoss;
		CSoundMgr::GetInst()->Monster6Sound(L"bossdeath.wav");
		return 1;
	}
	
	CBoss::WorldMatrix();
	list<CObj*>::iterator playeriter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	if(*(*playeriter)->GetRoomType() == m_RoomType)
	{
		FrameMove();
		if(pObjList[OBJ_BOSS_BIG].size() != 0)
		{
			if(*(*bossiter)->GetMonsterHp() < 10.f)
			{
				m_fSpeed = 1.5f;
				Tracking_Rage();
			}
			else
				Tracking_Float();
		}
		else if(pObjList[OBJ_BOSS_BIG].size() == 0)
		{
			m_fSpeed = 1.5f;
			Tracking_Rage();
		}
	}
	else
		m_dwState = BOSS_STAND;

	if(bInvincible == true)
	{
		if(m_dwTime + 1500 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}

	return 0;
}

void CSmallSteven::Render(void)
{
	CBoss::Render();	
}

void CSmallSteven::Release(void)
{
}
void CSmallSteven::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case BOSS_STAND:
			m_wstrStateKey = L"SmallSteaven_Normal_Left";
			m_tFrame = FRAME(0.f, 0.f, 3.f);
			break;
		case BOSS_FLOAT_LEFT:
			m_wstrStateKey = L"SmallSteaven_Normal_Left";
			m_tFrame = FRAME(0.f, 0.f, 3.f);
			break;
		case BOSS_FLOAT_RIGHT:
			m_wstrStateKey = L"SmallSteaven_Normal_Right";
			m_tFrame = FRAME(0.f, 0.f, 3.f);
			break;
		case BOSS_ATTACK_LEFT:
			m_wstrStateKey = L"SmallSteaven_Normal_Left";
			m_tFrame = FRAME(0.f, 10.f, 3.f);
			break;
		case BOSS_ATTACK_RIGHT:
			m_wstrStateKey = L"SmallSteaven_Normal_Right";
			m_tFrame = FRAME(0.f, 10.f, 3.f);
			break;
		case BOSS_RAGE_LEFT:
			m_wstrStateKey = L"SmallSteaven_Rage_Left";
			m_tFrame = FRAME(0.f, 10.f, 4.f);
			break;
		case BOSS_RAGE_RIGHT:
			m_wstrStateKey = L"SmallSteaven_Rage_Right";
			m_tFrame = FRAME(0.f, 10.f, 4.f);
			break;
		}
		m_dwPrevState = m_dwState;
	}

	
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(m_dwState != BOSS_STAND)
		{
			m_dwState = BOSS_STAND;
		}
		m_bCooldown = true;
		m_tFrame.fFrame = 0.f;
	}

}

void CSmallSteven::Tracking_Float()
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_BOSS_BIG].begin();
	list<CObj*>::iterator playeriter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	m_tInfo.vDir = (*iter)->GetInfo()->vPos - m_tInfo.vPos;

	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	if(m_tInfo.vDir.x < 0)
	{
		if((m_tInfo.vPos.x + 300 > (*playeriter)->GetInfo()->vPos.x && m_tInfo.vPos.x - 300 < (*playeriter)->GetInfo()->vPos.x)&&
			(m_tInfo.vPos.y + 300 > (*playeriter)->GetInfo()->vPos.y && m_tInfo.vPos.y - 300 < (*playeriter)->GetInfo()->vPos.y) && m_bCooldown == false)
		{
			m_dwState = BOSS_ATTACK_LEFT;
		}
		else
			m_dwState = BOSS_FLOAT_LEFT;
	}
	else if(m_tInfo.vDir.x > 0)
	{
		if((m_tInfo.vPos.x + 300 > (*playeriter)->GetInfo()->vPos.x && m_tInfo.vPos.x - 300 < (*playeriter)->GetInfo()->vPos.x)&&
			(m_tInfo.vPos.y + 300 > (*playeriter)->GetInfo()->vPos.y && m_tInfo.vPos.y - 300 < (*playeriter)->GetInfo()->vPos.y) && m_bCooldown == false)
		{
			m_dwState = BOSS_ATTACK_RIGHT;
		}
		else
			m_dwState = BOSS_FLOAT_RIGHT;
	}

	if(m_dwTime + 1500 < GetTickCount())
	{
			m_bCooldown = false;
			m_bBulletFired = false;
			m_attacksound = false;
			m_dwTime = GetTickCount();
	}
	if(m_tFrame.fFrame < 2.f && m_tFrame.fFrame > 1.f && m_bBulletFired == false)
	{
			D3DXVECTOR3 vTemp =(*playeriter)->GetInfo()->vPos - m_tInfo.vPos;
			D3DXVec3Normalize(&m_tInfo.vLook,&vTemp);
			if(m_attacksound == false)
			{
				CSoundMgr::GetInst()->Monster6Sound(L"bossattack.wav");
				m_attacksound = true;
			}
			CObjMgr::GetInst()->AddObj(OBJ_BULLET, CObjFactory<CBullet>::CreateObj(m_tInfo.vPos.x +m_tInfo.vLook.x, m_tInfo.vPos.y + m_tInfo.vLook.y,m_tInfo.vLook,NULL));
			m_bBulletFired = true;
	}
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
}

void CSmallSteven::Tracking_Rage(void)
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	m_tInfo.vDir = (*iter)->GetInfo()->vPos - m_tInfo.vPos;

	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	if(m_tInfo.vDir.x < 0)
	{
		m_dwState = BOSS_RAGE_LEFT;
	}
	else if(m_tInfo.vDir.x > 0)
	{
		m_dwState = BOSS_RAGE_RIGHT;
	}
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
}