#include "StdAfx.h"
#include "PassiveItem.h"

CPassiveItem::CPassiveItem(void)
{
}

CPassiveItem::~CPassiveItem(void)
{
}
HRESULT CPassiveItem::Initialize()
{
	m_bPassiveLoad = false;
	m_wstrObjKey = L"Item";
	m_wstrStateKey = L"Passive";
	m_RenderType = R_WORLDOBJ;
	return S_OK;
}
int CPassiveItem::Progress()
{
	if(m_bIsDead == true)
		return 1;
	ItemLoad();

	FrameMove();
	CItem::WorldMatrix();
	return 0;
}
void CPassiveItem::Render()
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if(pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CPassiveItem::Release()
{

}
void CPassiveItem::ItemLoad()
{
	if(m_bPassiveLoad == false)
	{
		for(float f = 0; f < 73.f; ++f)
		{
			if(m_dwState == f)
			{
				m_tFrame = FRAME(f,0.f,73.f);
				m_dwPrevState = (DWORD)f;
			}
		}
		m_bPassiveLoad = true;
	}
}
void CPassiveItem::FrameMove(void)
{
	switch(m_dwState)
	{
	case PS_SADONION:
		m_tFrame = FRAME(0.f, 0.f, 73.f);
		break;
	case PS_INNEREYE:
		m_tFrame = FRAME(1.f, 0.f, 73.f);
		break;
	case PS_SPOONBEND:
		m_tFrame = FRAME(2.f, 0.f, 73.f);
		break;
	case PS_CRICKETHEAD:
		m_tFrame = FRAME(3.f, 0.f, 73.f);
		break;
	case PS_NUMBER1:
		m_tFrame = FRAME(4.f, 0.f, 73.f);
		break;
	case PS_BLOODMARTYR:
		m_tFrame = FRAME(5.f, 0.f, 73.f);
		break;
	case PS_HALOOFFLY:
		m_tFrame = FRAME(6.f, 0.f, 73.f);
		break;
	case PS_MAGICMUSH:
		m_tFrame = FRAME(7.f, 0.f, 73.f);
		break;
	case PS_ROIDRAGE:
		m_tFrame = FRAME(8.f, 0.f, 73.f);
		break;
	case PS_HEART:
		m_tFrame = FRAME(9.f, 0.f, 73.f);
		break;
	case PS_RAWLIVER:
		m_tFrame = FRAME(10.f, 0.f, 73.f);
		break;
	case PS_SKELLTONKEY:
		m_tFrame = FRAME(11.f, 0.f, 73.f);
		break;
	case PS_ADOLLAR:
		m_tFrame = FRAME(12.f, 0.f, 73.f);
		break;
	case PS_BOOM:
		m_tFrame = FRAME(13.f, 0.f, 73.f);
		break;
	case PS_LUNCH:
		m_tFrame = FRAME(14.f, 0.f, 73.f);
		break;
	case PS_DINNER:
		m_tFrame = FRAME(15.f, 0.f, 73.f);
		break;
	case PS_DESSERT:
		m_tFrame = FRAME(16.f, 0.f, 73.f);
		break;
	case PS_BREAKFAST:
		m_tFrame = FRAME(17.f, 0.f, 73.f);
		break;
	case PS_ROTTENMEAT:
		m_tFrame = FRAME(18.f, 0.f, 73.f);
		break;
	case PS_WOODENSPOON:
		m_tFrame = FRAME(19.f, 0.f, 73.f);
		break;
	case PS_BELT:
		m_tFrame = FRAME(20.f, 0.f, 73.f);
		break;
	case PS_UNDERWEAR:
		m_tFrame = FRAME(21.f, 0.f, 73.f);
		break;
	case PS_HEEL:
		m_tFrame = FRAME(22.f, 0.f, 73.f);
		break;
	case PS_LIPSTICK:
		m_tFrame = FRAME(23.f, 0.f, 73.f);
		break;
	case PS_WIREHANGER:
		m_tFrame = FRAME(24.f, 0.f, 73.f);
		break;
	case PS_LUCKYFOOT:
		m_tFrame = FRAME(25.f, 0.f, 73.f);
		break;
	case PS_STEAVN:
		m_tFrame = FRAME(26.f, 0.f, 73.f);
		break;
	case PS_PENTAGRAM:
		m_tFrame = FRAME(27.f, 0.f, 73.f);
		break;
	case PS_DRFETUS:
		m_tFrame = FRAME(28.f, 0.f, 73.f);
		break;
	case PS_LADDER:
		m_tFrame = FRAME(29.f, 0.f, 73.f);
		break;
	case PS_GROWTHHHOROMONES:
		m_tFrame = FRAME(30.f, 0.f, 73.f);
		break;
	case PS_MINIMUSH:
		m_tFrame = FRAME(31.f, 0.f, 73.f);
		break;
	case PS_MEATCUBE:
		m_tFrame = FRAME(32.f, 0.f, 73.f);
		break;
	case PS_QUARTER:
		m_tFrame = FRAME(33.f, 0.f, 73.f);
		break;
	case PS_ROCK:
		m_tFrame = FRAME(34.f, 0.f, 73.f);
		break;
	case PS_HALO:
		m_tFrame = FRAME(35.f, 0.f, 73.f);
		break;
	case PS_MONEYPOWER:
		m_tFrame = FRAME(36.f, 0.f, 73.f);
		break;
	case PS_KINFE:
		m_tFrame = FRAME(37.f, 0.f, 73.f);
		break;
	case PS_BLOODBAG:
		m_tFrame = FRAME(38.f, 0.f, 73.f);
		break;
	case PS_ODDMUSH1:
		m_tFrame = FRAME(39.f, 0.f, 73.f);
		break;
	case PS_ODDMUSH2:
		m_tFrame = FRAME(40.f, 0.f, 73.f);
		break;
	case PS_LARD:
		m_tFrame = FRAME(41.f, 0.f, 73.f);
		break;
	case PS_STIGMATA:
		m_tFrame = FRAME(42.f, 0.f, 73.f);
		break;
	case PS_PAGEANT:
		m_tFrame = FRAME(43.f, 0.f, 73.f);
		break;
	case PS_SPEEDBALL:
		m_tFrame = FRAME(44.f, 0.f, 73.f);
		break;
	case PS_MUTANTSPIDER:
		m_tFrame = FRAME(45.f, 0.f, 73.f);
		break;
	case PS_BLOODYLUST:
		m_tFrame = FRAME(46.f, 0.f, 73.f);
		break;
	case PS_CELTICCROSS:
		m_tFrame = FRAME(47.f, 0.f, 73.f);
		break;
	case PS_NINEOCAT:
		m_tFrame = FRAME(48.f, 0.f, 73.f);
		break;
	case PS_EPICFETUS:
		m_tFrame = FRAME(49.f, 0.f, 73.f);
		break;
	case PS_POLYPHEMUS:
		m_tFrame = FRAME(50.f, 0.f, 73.f);
		break;
	case PS_STEMCELL:
		m_tFrame = FRAME(51.f, 0.f, 73.f);
		break;
	case PS_FATE:
		m_tFrame = FRAME(52.f, 0.f, 73.f);
		break;
	case PS_SACREDHEART:
		m_tFrame = FRAME(53.f, 0.f, 73.f);
		break;
	case PS_TOOTHSTICK:
		m_tFrame = FRAME(54.f, 0.f, 73.f);
		break;
	case PS_HOLYGRAIL:
		m_tFrame = FRAME(55.f, 0.f, 73.f);
		break;
	case PS_PYRO:
		m_tFrame = FRAME(56.f, 0.f, 73.f);
		break;
	case PS_MEAT:
		m_tFrame = FRAME(57.f, 0.f, 73.f);
		break;
	case PS_JESUSJUICE:
		m_tFrame = FRAME(58.f, 0.f, 73.f);
		break;
	case PS_BOX:
		m_tFrame = FRAME(59.f, 0.f, 73.f);
		break;
	case PS_LOSTCONTACT:
		m_tFrame = FRAME(60.f, 0.f, 73.f);
		break;
	case PS_MAGICSCAB:
		m_tFrame = FRAME(61.f, 0.f, 73.f);
		break;
	case PS_OLDBAND:
		m_tFrame = FRAME(62.f, 0.f, 73.f);
		break;
	case PS_2020:
		m_tFrame = FRAME(63.f, 0.f, 73.f);
		break;
	case PS_SCREW:
		m_tFrame = FRAME(64.f, 0.f, 73.f);
		break;
	case PS_MASCARA:
		m_tFrame = FRAME(65.f, 0.f, 73.f);
		break;
	case PS_BOW:
		m_tFrame = FRAME(66.f, 0.f, 73.f);
		break;
	case PS_POLAROID:
		m_tFrame = FRAME(67.f, 0.f, 73.f);
		break;
	case PS_DEADONION:
		m_tFrame = FRAME(68.f, 0.f, 73.f);
		break;
	case PS_SAFETYPIN:
		m_tFrame = FRAME(69.f, 0.f, 73.f);
		break;
	case PS_TORNPHOTO:
		m_tFrame = FRAME(70.f, 0.f, 73.f);
		break;
	case PS_SYNTHOIL:
		m_tFrame = FRAME(71.f, 0.f, 73.f);
		break;
	case PS_SNACK:
		m_tFrame = FRAME(72.f, 0.f, 73.f);
		break;

	}

}