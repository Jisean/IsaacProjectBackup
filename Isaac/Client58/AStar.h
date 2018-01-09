#pragma once

#include "define.h"

class CAStar
{
private:
	DECLARE_SINGLETON(CAStar)

	list<NODE*>			m_OpenList;
	list<NODE*>			m_CloseList;
	list<int>			m_BestList;

	int					m_iStartIndex;
	int					m_iGoalIndex;

public:
	void	AStarStart(const int& iStartIndex, const int& iGoalIndex);
	void	Release(void);

	void	MakeRoute(void);
	bool	CheckList(const int& iIndex);
	NODE*	MakeNode(int iIndex, NODE* pParent, const vector<TILE*>* pTile);

	static bool    Compare(const NODE* pTemp, const NODE* pDest);

	void	AStarStartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos);
	int		GetTileIndex(const D3DXVECTOR3& vPos);
	list<int>* GetBestList(void);	
	bool	Picking(const D3DXVECTOR3& vPos, const TILE* pTile);

private:
	CAStar(void);
	~CAStar(void);
};
