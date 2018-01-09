#pragma once
#include "scene.h"

class CStage :
	public CScene
{
private:
	bool m_bIntrostart;
	bool m_bIntroend;
	bool m_bBgmRoof;

	bool m_bShopintrostart;
	bool m_bShopintroend;
	bool m_bShopRoof;

	bool m_bBossRoofstart;
	bool m_bBossRoof;
	bool m_bBossjingle;

	bool m_bBosscalmintrostart;
	bool m_bBosscalmintroend;
	bool m_bBosscalmroof;

	DWORD dwBgmTime;

public:
	CStage(void);
	~CStage(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
