#pragma once

#include "Include.h"

class CTextureMgr;
class CDevice;
class CObj
{
protected:
	static		D3DXVECTOR3		m_vScroll;
	INFO			m_tInfo;
	CDevice*		m_pDevice;
	CTextureMgr*	m_pTexture;
	float			m_fSpeed;
	wstring			m_wstrObjKey;
	FRAME			m_tFrame;
	DWORD			m_dwState;
	DWORD			m_dwPrevState;
	wstring			m_wstrStateKey;
	FIREWAY			m_fireway;
	bool			m_bIsDead;
	DWORD			m_dwTime;
	DWORD			m_dwNumState;
	DWORD			m_dwState2;
	RENDERTYPE		m_RenderType;
	int				m_RoomType;
	float			m_fAngle;

	/////////////////////////////////////
	float			fAttack;
	float			fHp;
	int				iMaxHp;
	float			fTears;
	float			fShotSpeed;
	float			fSpeed;
	float			fRange;
	int				iLuck;
	int				iCoins;
	int				iKeys;
	int				iBombs;
	bool			bInvincible;
	//////////////////////////////////////
	bool			m_bTrack_Walk;
	bool			m_bTrack_Run;
	bool			m_bTired;

	//////////////////////////////////////
	

public:
	void		SetPos(D3DXVECTOR3 vPos);
	void		SetPos(float _fX, float _fY);
	void		SetPos(D3DXVECTOR3 vPos, FIREWAY _way);
	void		SetPos(float _fX, float _fY, FIREWAY _way);
	void		SetPos(D3DXVECTOR3 vPos, HUDTYPE _type);
	void		SetPos(D3DXVECTOR3 vPos, HUDNUMTYPE _type);
	void		SetPos(D3DXVECTOR3 vPos, PICKUP _type);
	void		SetPos(D3DXVECTOR3 vPos, PASSIVEITEM _type);
	void		SetPos2(float _fX, float _fY, PASSIVEITEM _type);
	void		SetPos(float _fX, float _fY, D3DXVECTOR3 _vDir, float Angle);
	void		SetPos(D3DXVECTOR3 vPos, EFFECT _type);
	void		SetPos(D3DXVECTOR3 vPos, BOSSHP _type);
	INFO*		GetInfo(void);
	const	wstring&	GetObjKey(void);
	void		SetDead(void);
	RENDERTYPE GetRenderType(void)
	{
		return m_RenderType;
	}
	float& GetTear(void)
	{
		return fTears;
	}
	float& GetSpeed(void)
	{
		return fSpeed;
	}
	int* GetCoin(void)
	{
		return &iCoins;
	}
	int* GetKey(void)
	{
		return &iKeys;
	}
	int* GetBomb(void)
	{
		return &iBombs;
	}
	void SetFrame(FRAME _frame)
	{
		m_tFrame = _frame;
	}
	float* GetPlayerHp(void)
	{
		return &fHp;
	}
	int* GetPlayerMaxHP(void)
	{
		return &iMaxHp;
	}
	void SetState(DWORD _state)
	{
		m_dwState = _state;
	}
	void SetHP(float _hp);
	void SetMaxHp(int _maxhp);
	void SetRange(float _range);
	void SetTear(float _tear);
	void SetSpeed(float _speed);
	void SetShotSpeed(float _shotspeed);
	void SetCoin(int _coin);
	void SetKey(int _key);
	void SetBomb(int _bomb);
	void SetAtt(float _att);
	void SetMonHp(float _hp);
	DWORD* GetItemName(void)
	{
		return &m_dwState;
	}
	FIREWAY* GetFireWay(void)
	{
		return &m_fireway;
	}
	float* GetMonsterSpeed(void)
	{
		return &m_fSpeed;
	}
	int* GetRoomType(void)
	{
		return &m_RoomType;
	}
	void SetRoomTypeRight(void)
	{
		++m_RoomType;
	}
	void SetRoomTypeLeft(void)
	{
		--m_RoomType;
	}
	void SetRoomTypeUp(void)
	{
		m_RoomType -= 10;
	}
	void SetRoomTypeDown(void)
	{
		m_RoomType += 10;
	}
	bool* GetBossTired(void)
	{
		return &m_bTired;
	}
	bool* GetBossWalk(void)
	{
		return &m_bTrack_Walk;
	}
	bool* GetBossRun(void)
	{
		return &m_bTrack_Run;
	}
	bool* GetDeadState(void)
	{
		return &m_bIsDead;
	}
	float* GetMonsterHp(void)
	{
		return &fHp;
	}

	void SetInvincible(void)
	{
		bInvincible = true;
	}

	bool* GetInvincible(void)
	{
		return &bInvincible;
	}





public:
	virtual HRESULT	Initialize(void)PURE;
	virtual int		Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
