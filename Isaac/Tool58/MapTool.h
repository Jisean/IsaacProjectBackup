#pragma once
#include "afxwin.h"
#include "Resource.h"



// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAPTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:		// control type
	CListBox m_ListBox;
	CStatic m_Picture;
	CButton m_iRadio[15];
public:
	map<CString, CImage*>		m_MapPngImage; 
	int							m_iDrawID;
	bool	m_bStart;
	static int m_iState;


public:
	void HorizontalScroll(void);

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	afx_msg void OnListBox();
	afx_msg void OnSaveButton();

	
	
	afx_msg void OnOptionChange();
};
