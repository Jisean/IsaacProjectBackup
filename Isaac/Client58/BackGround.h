#pragma once
#include "obj.h"

class CBackGround :
	public CObj
{
private:
	vector<TILE*>		m_vecTile;

	int			m_iTileRenderX;
	int			m_iTileRenderY;
	HDC			m_DC;


public:
	CBackGround(void);
	~CBackGround(void);

private:
	void	LoadTile(const wstring& wstrPath);
public:
	const vector<TILE*>* GetTile(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
