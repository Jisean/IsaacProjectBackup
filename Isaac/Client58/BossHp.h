#pragma once
#include "ui.h"

class CBossHp :
	public CUI
{
private:
	bool m_bUILoad;
	RECT	rcHpBar;

public:
	void FrameMove(void);
	void WorldMatrix(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CBossHp(void);
	~CBossHp(void);
};
