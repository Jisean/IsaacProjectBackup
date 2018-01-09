#pragma once
#include "obj.h"

class CTool58View;
class CMapTool;
class CBack :
	public CObj
{
private:
	vector<TILE*>		m_vecTile;
	CTool58View*		m_pMainView;
	CMapTool*			m_pMapTool;

public:
	int	GetTileIndex(const D3DXVECTOR3& vPos);
	void TileChange(const D3DXVECTOR3& vPos, const int& iDrawID);
	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);

	void SetMainView(CTool58View* pMainView);

	void MiniViewRender(void);	

	const vector<TILE*>*		GetTile(void);

public:
	CBack(void);
	~CBack(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
