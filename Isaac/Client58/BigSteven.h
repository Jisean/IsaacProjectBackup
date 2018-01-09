#pragma once
#include "boss.h"

class CBigSteven :
	public CBoss
{
protected:
	bool m_bHasBodynHead;
	bool b_soundroar;
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CBigSteven(void);
	~CBigSteven(void);
};
