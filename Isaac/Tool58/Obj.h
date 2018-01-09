#pragma once

#include "Include.h"

class CDevice;
class CTextureMgr;
class CObj
{
protected:
	INFO			m_tInfo;
	CDevice*		m_pDevice;
	CTextureMgr*	m_pTexture;

public:
	void		SetPos(D3DXVECTOR3& vPos);
	void		SetPos(float _fX, float _fY);

public:
	virtual HRESULT		Initialize(void)	PURE;
	virtual int			Progress(void)		PURE;
	virtual void		Render(void)		PURE;
	virtual void		Release(void)		PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
