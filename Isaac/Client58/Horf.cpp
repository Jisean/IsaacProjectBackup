#include "StdAfx.h"
#include "Horf.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Bullet.h"
#include "SoundMgr.h"
CHorf::CHorf(void)
{
}

CHorf::~CHorf(void)
{
}
HRESULT CHorf::Initialize(void)
{
	fHp = 3.f;
	m_wstrObjKey = L"Horf";
	m_wstrStateKey = L"Normal";
	m_dwState = MS_STAND;
	m_dwPrevState = MS_STAND;
	m_tFrame = FRAME(0.f, 0.f, 3.f);
	m_tInfo.vSize = D3DXVECTOR3(38.f,30.f,0.f);
	m_fSpeed = 0.f;
	m_RenderType = R_WORLDOBJ;
	m_bCooldown = false;
	m_bBulletFired = false;
	m_bAttacksound = false;
	m_RoomType = 1;
	return S_OK;
}

int CHorf::Progress(void)
{
	if(m_bIsDead == true)
	{
		--g_iRoomMobCnt1;
		CSoundMgr::GetInst()->Monster2Sound(L"mobdeath1.wav");
		return 1;
	}
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	
	CMonster::WorldMatrix();


	if(*(*iter)->GetRoomType() == m_RoomType)
	{
		srand((unsigned)time(NULL));
		FrameMove();
		if((m_tInfo.vPos.x + 300 > (*iter)->GetInfo()->vPos.x && m_tInfo.vPos.x - 300 < (*iter)->GetInfo()->vPos.x)&&
			(m_tInfo.vPos.y + 300 > (*iter)->GetInfo()->vPos.y && m_tInfo.vPos.y - 300 < (*iter)->GetInfo()->vPos.y) && m_bCooldown == false)
		{
			m_dwState = MS_ATTACK;
		}
		else
		{
			m_dwState = MS_STAND;
		}

		if(m_dwTime + 1500 < GetTickCount())
		{
			m_bCooldown = false;
			m_bBulletFired = false;
			m_bAttacksound = false;
			m_dwTime = GetTickCount();
		}
		if(m_tFrame.fFrame < 2.f && m_tFrame.fFrame > 1.f && m_bBulletFired == false)
		{
			list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();

			D3DXVECTOR3 vTemp =(*iter)->GetInfo()->vPos - m_tInfo.vPos;
			D3DXVec3Normalize(&m_tInfo.vLook,&vTemp);
			if(m_bAttacksound == false)
			{
				if(rand()%2 == 0)
				{
					CSoundMgr::GetInst()->Monster1Sound(L"horfattack.wav");
					m_bAttacksound = true;
				}
				else
				{
					CSoundMgr::GetInst()->Monster1Sound(L"horfattack2.wav");

				}
			}
			CObjMgr::GetInst()->AddObj(OBJ_BULLET, CObjFactory<CBullet>::CreateObj(m_tInfo.vPos.x +m_tInfo.vLook.x, m_tInfo.vPos.y + m_tInfo.vLook.y,m_tInfo.vLook,NULL));
			m_bBulletFired = true;
		}
	}
	return 0;
}

void CHorf::Render(void)
{
	CMonster::Render();	
}

void CHorf::Release(void)
{
}
void CHorf::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case MS_STAND:
			m_tFrame = FRAME(0.f, 0.f, 3.f);
			break;
		case MS_ATTACK:
			m_tFrame = FRAME(0.f, 10.f, 3.f);
			break;
		}
		m_dwPrevState = m_dwState;
	}


	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(m_dwState != MS_STAND)
		{
			m_dwState = MS_STAND;
		}

		m_bCooldown = true;
		m_tFrame.fFrame = 0.f;
	}

}