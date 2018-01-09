#pragma once
#include "UI.h"

class CPickupUI :
	public CUI
{
private:
	int m_iCoin;
	int m_iBomb;
	int m_iKey;
	bool m_bUILoad;
public:
	void FrameMove(void);
	void CoinHud(void);
	void KeyHud(void);
	void BombHud(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CPickupUI(void);
	~CPickupUI(void);
};
