#include "StdAfx.h"
#include "HpUI.h"
#include "Objmgr.h"
#include "ObjFactory.h"

CHpUI::CHpUI(void)
{
}

CHpUI::~CHpUI(void)
{
}
HRESULT	CHpUI::Initialize()
{
	m_wstrObjKey = L"UI";
	m_wstrStateKey = L"HP";
	m_dwState = HS_FULL;
	m_tFrame = FRAME(0.f,0.f,1.f);
	m_RenderType = R_UI;
	return S_OK;
}

int CHpUI::Progress()
{
	MaxHpCheck();
	HPCheck();
	FrameMove();
	CUI::WorldMatrix();
	return 0;
}

void CHpUI::Render()
{
	CUI::Render();
}

void CHpUI::Release()
{

}
void CHpUI::FrameMove(void)
{
	switch(m_dwState)
	{
	case HS_FULL:
		m_tFrame = FRAME(0.f, 0.f, 3.f);
		break;
	case HS_HALF:
		m_tFrame = FRAME(1.f, 0.f, 3.f);
		break;
	case HS_ZERO:
		m_tFrame = FRAME(2.f, 0.f, 3.f);
		break;
	}

}
void CHpUI::HPCheck()
{

	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
	list<CObj*>::iterator Hpiter_end = CObjMgr::GetInst()->GetObjList()[OBJ_UI_HP].end();
	list<CObj*>::iterator Hpiter_start = CObjMgr::GetInst()->GetObjList()[OBJ_UI_HP].begin();

	--Hpiter_end;

	float fHp = *(*iter)->GetPlayerHp();
	int   iMaxHp =*(*iter)->GetPlayerMaxHP();


	if(iMaxHp - fHp == 0.f)
	{
		for(Hpiter_start; Hpiter_start != Hpiter_end; ++Hpiter_start)
			(*Hpiter_start)->SetState(HS_FULL);
		(*Hpiter_end)->SetState(HS_FULL);
	}

	else
	{
		for(int i = 0; i < iMaxHp; ++i)
		{
			if(iMaxHp - fHp == 0.5f)
			{
				(*Hpiter_end)->SetState(HS_HALF);
				--Hpiter_end;
				for(Hpiter_start; Hpiter_start != Hpiter_end; ++Hpiter_start)
				{
					(*Hpiter_end)->SetState(HS_FULL);
				}
				(*Hpiter_start)->SetState(HS_FULL);
				break;
			}
			else if(iMaxHp - fHp == i - 0.5f && iMaxHp - fHp != 0.5f)
			{
				for(int j = 0; j < i - 1; ++j)
				{
					(*Hpiter_end)->SetState(HS_ZERO);
					--Hpiter_end;
				}
				(*Hpiter_end)->SetState(HS_HALF);
				--Hpiter_end;
				for(Hpiter_start; Hpiter_start != Hpiter_end; ++Hpiter_start)
				{
					(*Hpiter_end)->SetState(HS_FULL);
				}
				(*Hpiter_start)->SetState(HS_FULL);
				break;

			}
			else if(iMaxHp - fHp == i && iMaxHp - fHp != 0.f)
			{
				for(int j = 0; j < i; ++j)
				{
					(*Hpiter_end)->SetState(HS_ZERO);
					--Hpiter_end;
				}
				for(Hpiter_start; Hpiter_start != Hpiter_end; ++Hpiter_start)
				{
					(*Hpiter_end)->SetState(HS_FULL);
				}
				(*Hpiter_start)->SetState(HS_FULL);
				break;
			}
			else if(iMaxHp - fHp == iMaxHp - 0.5f)
			{
				for(int j = 0; j < iMaxHp - 1; ++j)
				{
					(*Hpiter_end)->SetState(HS_ZERO);
					--Hpiter_end;
				}
				(*Hpiter_start)->SetState(HS_HALF);
				break;
			}
		}
	}
}



void CHpUI::MaxHpCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();

	m_iCount = *(*iter)->GetPlayerMaxHP();

	m_iMaxHPCount = CObjMgr::GetInst()->GetObjList()[OBJ_UI_HP].size();

	if(m_iCount > m_iMaxHPCount)
	{
		list<CObj*>::iterator HPiter = CObjMgr::GetInst()->GetObjList()[OBJ_UI_HP].end();
		--HPiter;

		float HPposX = (*HPiter)->GetInfo()->vPos.x;
		CObjMgr::GetInst()->AddObj(OBJ_UI_HP,
			CObjFactory<CHpUI>::CreateObj(HPposX + 22.f ,50.f));
	}

	else if(m_iCount < m_iMaxHPCount)
	{
		CObjMgr::GetInst()->GetObjList()[OBJ_UI_HP].pop_back();
	}
}

