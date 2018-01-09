#pragma once
#include "ui.h"

class CHpUI :
	public CUI
{
private:
	int m_iMaxHPCount;
public:
	void FrameMove(void);
	void MaxHpCheck(void);
	void HPCheck(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CHpUI(void);
	~CHpUI(void);
};
