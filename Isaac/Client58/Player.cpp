#include "StdAfx.h"
#include "Player.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include "ObjMgr.h"
#include "Player_Body.h"
#include "Player_Head.h"
#include "Bomb.h"
#include "SoundMgr.h"
#include "Missile.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_vecOffset = D3DXVECTOR3(500.f, 400.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(18.f, 15.f, 0.f);
	m_fSpeed = 300.f;
	m_RenderType = R_WORLDOBJ;
	m_RoomType = 0;
	m_bHasBodynHead = false;
	bInvincible = false;
	m_bBlinking = false;
	StatLoad(L"Isaac");

	fSpeed = 2.f;

	return S_OK;
}

int CPlayer::Progress(void)
{

	if(m_bHasBodynHead == false)
	{
		CObjMgr::GetInst()->AddObj(OBJ_PLAYER_BODY, 
			CObjFactory<CPlayer_Body>::CreateObj(m_tInfo.vPos));
		CObjMgr::GetInst()->AddObj(OBJ_PLAYER_HEAD, 
			CObjFactory<CPlayer_Head>::CreateObj(m_tInfo.vPos.x + 1, m_tInfo.vPos.y - 26.5f));

		m_bHasBodynHead = true;
	}

	WorldMatrix();
	KeyInput();
	Scroll();
	//DynamicScroll();
	//AStarMove();

	cout << "X : " << m_tInfo.vPos.x << endl;
	cout << "Y : " << m_tInfo.vPos.y << endl;

	//cout << m_RoomType << endl;

	/*cout << "HP:"<< fHp << endl;
	cout << "MaxHP:" << iMaxHp << endl;*/

	if(bInvincible == true)
	{
		if(m_dwTime + 3000 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}



	return 0;
}

void CPlayer::Render(void)
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if(pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	if(bInvincible == false)
	{
	m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(155, 255, 255, 255));

	}
}
void CPlayer::Release(void)
{
}


void CPlayer::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}

void CPlayer::KeyInput(void)
{
	if(CKeyMgr::GetInst()->KeyPressed(KEY_LBUTTON) && g_bEpicFetus == true)
	{
		D3DXVECTOR3	vMousePos = ::GetMouse() - m_vScroll;
		CObjMgr::GetInst()->AddObj(OBJ_BOMB, CObjFactory<CMissile>::CreateObj(vMousePos));

	}

	if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
	{
		m_tInfo.vPos.y -= fSpeed;
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
	{
		m_tInfo.vPos.y += fSpeed;
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
	{
		m_tInfo.vPos.x -= fSpeed;
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
	{
		m_tInfo.vPos.x += fSpeed;

	}
	if(CKeyMgr::GetInst()->KeyPressed(KEY_CTRL))
	{
		if(iBombs > 0)
		{
			--iBombs;
			CSoundMgr::GetInst()->PlaySkillSound(L"bombset.wav");
			CObjMgr::GetInst()->AddObj(OBJ_BOMB, CObjFactory<CBomb>::CreateObj(m_tInfo.vPos));
		}
	}

	if(CKeyMgr::GetInst()->KeyPressed(KEY_1))
	{
		fHp += 0.5f;
	}
	if(CKeyMgr::GetInst()->KeyPressed(KEY_2))
	{
		fHp -= 0.5f;
	}
	if(CKeyMgr::GetInst()->KeyPressed(KEY_3))
	{
		++iMaxHp;
	}
	if(CKeyMgr::GetInst()->KeyPressed(KEY_4))
	{
		--iMaxHp;
	}

}

void CPlayer::AStarMove(void)
{
	list<int>* pBestList = CAStar::GetInst()->GetBestList();

	if(pBestList->empty())
		return;

	const vector<TILE*>*	pVecTile = CObjMgr::GetInst()->GetTile();

	if(pVecTile == NULL)
		return;

	int iMoveIndex = pBestList->front();

	m_tInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - m_tInfo.vPos;

	float fDistance = D3DXVec3Length(&m_tInfo.vDir);

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * GET_TIME;

	if(fDistance < 5.f)
	{
		pBestList->pop_front();
	}


}

void CPlayer::Scroll(void)
{
	//플레이어x랑 스크롤을 더한 값이
	//화면 중앙 + 오프셋보다 커졌을 떄 (오른쪽)

	const TEXINFO* pTexture = m_pTexture->GetTexture(L"BASEMENT", L"Basement",NULL);

	if(m_tInfo.vPos.x + m_vScroll.x > WINCX / 2 + m_vecOffset.x)
	{
		//스크롤 값을 빼준다..
		for(float f=0.f; f < 108.7 ; f += 0.1f)
		{
			m_vScroll.x -= int(1.f);
		}

		//그려야 되는 이미지를 넘어가려고 하면 고정시킨다.
		if(m_vScroll.x > (float)pTexture->tImgInfo.Width - WINCX)
			m_vScroll.x = (float)pTexture->tImgInfo.Width - WINCX;
	}
	if(m_tInfo.vPos.x + m_vScroll.x < WINCX / 2 - m_vecOffset.x)
	{
		for(float f=0.f; f < 108.7 ; f += 0.1f)
		{
			m_vScroll.x += int(1.f);
		}

		if(m_vScroll.x > 0)
			m_vScroll.x = 0;
	}
	if(m_tInfo.vPos.y + m_vScroll.y > WINCY / 2 + m_vecOffset.y)
	{
		for(float f=0.f; f < 75.8 ; f += 0.1f)
			m_vScroll.y -= int(1.f);

		if(m_vScroll.y > (float)pTexture->tImgInfo.Height - WINCY)
			m_vScroll.y = (float) pTexture->tImgInfo.Height - WINCY;
	}
	if(m_tInfo.vPos.y  + m_vScroll.y < WINCY / 2 - m_vecOffset.y)
	{
		for(float f=0.f; f < 75.8 ; f += 0.1f)
			m_vScroll.y += int(1.f);

		if(m_vScroll.y > 0)
			m_vScroll.y = 0;
	}
}
void CPlayer::StatLoad(const wstring& wstrName)
{
	HANDLE	hFile = CreateFile(L"../Data/Char.dat", GENERIC_READ, 
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwByte;


	while(true)
	{
		UNITDATA* pData = new UNITDATA;
		ReadFile(hFile,pData,sizeof(UNITDATA),&dwByte,NULL);
		if(dwByte == 0)
		{
			Safe_Delete(pData);
			break;
		}

		m_mapStat.insert(make_pair(pData->wstrName.c_str(),pData));
	}
	map<wstring, UNITDATA*>::iterator iter = m_mapStat.find(wstrName);

	fAttack = (*iter).second->fAttack;
	fHp = (float)(*iter).second->iHp;
	iMaxHp = (int)fHp;
	fTears = (*iter).second->fTears;
	fShotSpeed = (*iter).second->fShotSpeed;
	fSpeed = (*iter).second->fSpeed;
	fRange = (*iter).second->fRange;
	iLuck = (*iter).second->iLuck;
	iCoins = (*iter).second->iCoins;
	iKeys = (*iter).second->iKeys;
	iBombs = (*iter).second->iBombs;

	CloseHandle(hFile);


	

}

void CPlayer::DynamicScroll(void)
{

		const TEXINFO* pTexture = m_pTexture->GetTexture(L"BASEMENT", L"Basement",NULL);

	//오른쪽
	//넘어갔을 때 (플레이어가 화면 중앙을 오른쪽으로 넘어갈 때)
	if(m_tInfo.vPos.x + m_vScroll.x > WINCX / 2)
	{
		float fScrollSpeed = (m_tInfo.vPos.x + m_vScroll.x) - WINCX / 2;
		fScrollSpeed /= 32.f;

		m_vScroll.x -= (int)fScrollSpeed;

		if(m_vScroll.x < WINCX - (float)pTexture->tImgInfo.Width)
			m_vScroll.x = WINCX - (float)pTexture->tImgInfo.Width;
	}
	if(m_tInfo.vPos.x + m_vScroll.x < WINCX / 2)
	{
		float fScrollSpeed = (WINCX / 2 - (m_tInfo.vPos.x + m_vScroll.x));
		fScrollSpeed /= 32.f;

		m_vScroll.x += (int)fScrollSpeed;

		if(m_vScroll.x > 0)
			m_vScroll.x = 0;
	}

	if(m_tInfo.vPos.y + m_vScroll.y > WINCY / 2)
	{
		float fScrollSpeed = (m_tInfo.vPos.y + m_vScroll.y) - WINCY / 2;
		fScrollSpeed /= 32.f;

		m_vScroll.y -= (int)fScrollSpeed;

		if(m_vScroll.y < WINCY - (float)pTexture->tImgInfo.Height)
			m_vScroll.y = WINCY - (float)pTexture->tImgInfo.Height;
	}

	if(m_tInfo.vPos.y + m_vScroll.y < WINCY / 2)
	{
		float fScrollSpeed = WINCY / 2 - (m_tInfo.vPos.y + m_vScroll.y);
		fScrollSpeed /= 32.f;

		m_vScroll.y += (int)fScrollSpeed;

		if(m_vScroll.y > 0)
			m_vScroll.y = 0;
	}
}
