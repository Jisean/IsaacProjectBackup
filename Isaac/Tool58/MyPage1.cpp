// MyPage1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool58.h"
#include "MyPage1.h"


// CMyPage1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(CMyPage1::IDD)
{

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
END_MESSAGE_MAP()


// CMyPage1 메시지 처리기입니다.
