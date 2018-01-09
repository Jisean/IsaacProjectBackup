// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool58.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(CMyForm::IDD)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnMapTool)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyForm::OnPathFind)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_Font.CreatePointFont(100, L"comic sans ms");
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON9)->SetFont(&m_Font);
}

void CMyForm::OnUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(m_UnitTool.GetSafeHwnd() == NULL)
	{
		m_UnitTool.Create(IDD_UNITTOOL);
	}
	
	m_UnitTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(m_MapTool.GetSafeHwnd() == NULL)
	{
		m_MapTool.Create(IDD_MAPTOOL);
	}

	m_MapTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnPathFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(m_PathFind.GetSafeHwnd() == NULL)
	{
		m_PathFind.Create(IDD_PATHFIND);
	}

	m_PathFind.ShowWindow(SW_SHOW);
}
