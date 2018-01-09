#include "StdAfx.h"
#include "AStar.h"
#include "ObjMgr.h"

IMPLEMENT_SINGLETON(CAStar)

CAStar::CAStar(void)
: m_iStartIndex(0),
 m_iGoalIndex(0)
{
}

CAStar::~CAStar(void)
{
	Release();
}

void CAStar::AStarStart(const int& iStartIndex, const int& iGoalIndex)
{
		if(iStartIndex == iGoalIndex)
			return ;

		const vector<TILE*>*	pVecTile = CObjMgr::GetInst()->GetTile();

		if(pVecTile == NULL)
			return;

		//0. 이동가능 1. 이동불가 2.가시 3.X 4.돌 
		//5.불 6.벽 7.닫힌 왼문 8.열린 왼문 9.닫힌 오른문 
		//10.열린 오른문 11. 닫힌 윗문 12.열린 윗문 13.닫힌 아랫문 14.열린 아랫문
		if((*pVecTile)[iGoalIndex]->byOption == 1)
			return;

		Release();

		m_iStartIndex = iStartIndex;
		m_iGoalIndex  = iGoalIndex;

		MakeRoute();
}

void CAStar::Release(void)
{
	for_each(m_OpenList.begin(), m_OpenList.end(), DELETEOBJ());
	m_OpenList.clear();

	for_each(m_CloseList.begin(), m_CloseList.end(), DELETEOBJ());
	m_CloseList.clear();

	m_BestList.clear();
}

void CAStar::MakeRoute(void)
{
	NODE*		pParent = new NODE;
	pParent->iIndex  = m_iStartIndex;
	pParent->pParent = NULL;
	pParent->fCost   = 0.f;

	m_CloseList.push_back(pParent);

	const vector<TILE*>*	pVecTile = CObjMgr::GetInst()->GetTile();

	if(pVecTile == NULL)
		return;

	NODE*	pNode = NULL;
	int		iIndex = 0;

	// 1. 맵 상에 존재하는 인덱스인가?
	// 2. 옵션 값이 '0'인가?
	// 3. 오픈리스트 or 클로즈리스트에 포함되어 있는 타일인가?

	while(true)
	{

		// 윗 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex - TILEX;

		if(pParent->iIndex >= TILEX * 2      &&
		  (*pVecTile)[iIndex]->byOption == 0 && 
		  CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		// 아래 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex + TILEX;

		if(pParent->iIndex < TILEX * TILEY - (TILEX * 2)  &&
			(*pVecTile)[iIndex]->byOption == 0 && 
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		// 왼쪽 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex - 1;

		if(pParent->iIndex % TILEX != 0        &&
			(*pVecTile)[iIndex]->byOption == 0 && 
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		// 오른쪽 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex + 1;

		if(pParent->iIndex % TILEX != TILEX -1 &&
			(*pVecTile)[iIndex]->byOption == 0 && 
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		// 오른쪽 윗 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex - (TILEX - (pParent->iIndex / TILEX) % 2);

		if(pParent->iIndex >= TILEX &&
		pParent->iIndex % (TILEX * 2) != (TILEX  * 2) - 1 &&
			(*pVecTile)[iIndex]->byOption == 0 && 
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		// 오른쪽 아랫 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex + (TILEX + (pParent->iIndex / TILEX) % 2);

		if(pParent->iIndex < (TILEX  * TILEY) - TILEX &&
			pParent->iIndex % (TILEX * 2) != (TILEX  * 2) - 1 &&
			(*pVecTile)[iIndex]->byOption == 0 && 
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		// 왼쪽 아랫 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex + (TILEX + (pParent->iIndex / TILEX) % 2) - 1;

		if(pParent->iIndex < (TILEX  * TILEY) - TILEX &&
			pParent->iIndex % (TILEX * 2) != 0 &&
			(*pVecTile)[iIndex]->byOption == 0 && 
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		// 왼쪽 윗 방향 이동에 대한 예외 처리
		iIndex = pParent->iIndex - (TILEX + (pParent->iIndex / TILEX + 1) % 2);

		if(pParent->iIndex >= TILEX &&
			pParent->iIndex % (TILEX * 2) != 0 &&
			(*pVecTile)[iIndex]->byOption == 0 && 
			CheckList(iIndex))
		{
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);
		}

		///////////////////////////////////////////// 7방향 검사

		m_OpenList.sort(Compare);

		list<NODE*>::iterator iter = m_OpenList.begin();
		if(m_OpenList.size() == 0)
			break;

		m_CloseList.push_back(*iter);
		pParent = *iter;

		m_OpenList.erase(iter);

		if(pParent->iIndex == m_iGoalIndex)
		{
			while(true)
			{
				m_BestList.push_back(pParent->iIndex);
				pParent = pParent->pParent;

				if(pParent->iIndex == m_iStartIndex)
					break;
			}

			m_BestList.reverse();
			break;
		}
	}

}

bool CAStar::CheckList(const int& iIndex)
{
	for(list<NODE*>::iterator	iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}

	for(list<NODE*>::iterator	iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}
	
	return true;
}

NODE* CAStar::MakeNode(int iIndex, NODE* pParent, const vector<TILE*>* pTile)
{
	NODE*		pNode = new NODE;

	pNode->iIndex  = iIndex;
	pNode->pParent = pParent;

	D3DXVECTOR3	vDistance = (*pTile)[iIndex]->vPos - (*pTile)[pParent->iIndex]->vPos;
	float		fPCost = D3DXVec3Length(&vDistance);

	D3DXVECTOR3	vGoalDistance = (*pTile)[iIndex]->vPos - (*pTile)[m_iGoalIndex]->vPos;
	float		fGCost = D3DXVec3Length(&vGoalDistance);

	pNode->fCost = fPCost + fGCost;

	return pNode;
}

bool CAStar::Compare(const NODE* pTemp, const NODE* pDest)
{
	return pTemp->fCost < pDest->fCost;
}

void CAStar::AStarStartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos)
{
	m_iStartIndex = GetTileIndex(vStartPos);
	m_iGoalIndex  = GetTileIndex(vGoalPos);

	if(m_iStartIndex < 0 || m_iGoalIndex < 0)
		return;

	AStarStart(m_iStartIndex, m_iGoalIndex);
}

int CAStar::GetTileIndex(const D3DXVECTOR3& vPos)
{
	const vector<TILE*>*	pVecTile = CObjMgr::GetInst()->GetTile();

	if(pVecTile == NULL) 
		return -1;

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		if(Picking(vPos, (*pVecTile)[i]))	
		{
			return i;
		}
	}

	return -1; 
}

list<int>* CAStar::GetBestList(void)
{
	return &m_BestList;
}

bool CAStar::Picking(const D3DXVECTOR3& vPos, const TILE* pTile)
{
	float		fGradient = (TILECY / 2.f ) / (TILECX / 2.f);

	D3DXVECTOR3		vPoint[4] = 
	{
		D3DXVECTOR3(pTile->vPos.x, pTile->vPos.y - TILECY / 2.f, 0.f),
		D3DXVECTOR3(pTile->vPos.x + TILECX / 2.f, pTile->vPos.y, 0.f),
		D3DXVECTOR3(pTile->vPos.x, pTile->vPos.y + TILECY / 2.f, 0.f),
		D3DXVECTOR3(pTile->vPos.x - TILECX / 2.f, pTile->vPos.y, 0.f),
	}; 

	// Y = AX + B -> B = Y - AX

	float	fB[4] = 
	{
		vPoint[0].y - fGradient * vPoint[0].x,
		vPoint[1].y + fGradient * vPoint[1].x,
		vPoint[2].y - fGradient * vPoint[2].x,
		vPoint[3].y + fGradient * vPoint[3].x
	};

	// y = ax + b
	// y - ax - b == 0 직선 상
	// y - ax - b > 0 직선 위	(0, 3)
	// y - ax - b < 0 직선 아래 (1, 2)

	if(vPos.y - fGradient * vPos.x - fB[0] >= 0 &&
		vPos.y + fGradient * vPos.x - fB[1] < 0 &&
		vPos.y - fGradient * vPos.x - fB[2] < 0 &&
		vPos.y + fGradient * vPos.x - fB[3] >= 0 )
	{
		return true;
	}


	return false;
}
