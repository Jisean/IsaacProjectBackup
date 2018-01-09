#pragma once

#define			NO_COPY(CLASSNAME)					\
				private:							\
				CLASSNAME(const CLASSNAME&);		\
				CLASSNAME& operator = (const CLASSNAME&); 

#define			DECLARE_SINGLETON(CLASSNAME)			\
				NO_COPY(CLASSNAME)						\
				private:								\
					static CLASSNAME*		pInstance;	\
				public:									\
					static CLASSNAME*	GetInst(void);	\
					static void			DestroyInst(void);	

#define			IMPLEMENT_SINGLETON(CLASSNAME)		\
		 CLASSNAME* CLASSNAME::pInstance = NULL;	\
		 CLASSNAME*	CLASSNAME::GetInst(void)		\
			{										\
				if(pInstance == NULL)				\
				{									\
					pInstance = new CLASSNAME;		\
				}									\
				return pInstance;					\
			}										\
			void CLASSNAME::DestroyInst(void)		\
			{										\
				if(pInstance != NULL)				\
				{									\
					delete pInstance;				\
					pInstance = NULL;				\
				}									\
			}


class CStringCompare
{
public:
	explicit CStringCompare(const TCHAR* pKey)
		: m_pString(pKey) {}
	~CStringCompare() {}
public:
	template <typename T>
	bool operator () (T Data)
	{
		return !lstrcmp(Data.first, m_pString);
	}
private:
	const TCHAR*	m_pString;
};

#define			ERR_MSG(Message)MessageBox(g_hWnd, Message, L"System Error", NULL)

#define			GET_TIME CTimeMgr::GetInst()->GetTime()