// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool58.h"
#include "MapTool.h"
#include "FileInfo.h"
#include "Back.h"
#include "MainFrm.h"
#include "Tool58View.h"


// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)
int CMapTool::m_iState = 0;
CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(CMapTool::IDD, pParent)
	, m_bStart(true)
{
	//m_iDrawID = 0;
}

CMapTool::~CMapTool()
{
	for(map<CString, CImage*>::iterator iter = m_MapPngImage.begin();
		iter != m_MapPngImage.end(); ++iter)
	{
		iter->second->Destroy();
		::Safe_Delete(iter->second);
	}
	m_MapPngImage.clear();

}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_RADIO1, m_iRadio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_iRadio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_iRadio[2]);
	DDX_Control(pDX, IDC_RADIO4, m_iRadio[3]);
	DDX_Control(pDX, IDC_RADIO5, m_iRadio[4]);
	DDX_Control(pDX, IDC_RADIO6, m_iRadio[5]);
	DDX_Control(pDX, IDC_RADIO7, m_iRadio[6]);
	DDX_Control(pDX, IDC_RADIO8, m_iRadio[7]);
	DDX_Control(pDX, IDC_RADIO9, m_iRadio[8]);
	DDX_Control(pDX, IDC_RADIO10, m_iRadio[9]);
	DDX_Control(pDX, IDC_RADIO11, m_iRadio[10]);
	DDX_Control(pDX, IDC_RADIO12, m_iRadio[11]);
	DDX_Control(pDX, IDC_RADIO13, m_iRadio[12]);
	DDX_Control(pDX, IDC_RADIO14, m_iRadio[13]);
	DDX_Control(pDX, IDC_RADIO15, m_iRadio[14]);

	if(m_bStart)
	{
		m_iRadio[0].SetCheck(TRUE);
		m_bStart = false;
	}


}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnSaveButton)
	ON_BN_CLICKED(IDC_RADIO1, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO2, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO3, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO4, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO5, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO6, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO7, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO8, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO9, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO10, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO11, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO12, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO13, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO14, &CMapTool::OnOptionChange)
	ON_BN_CLICKED(IDC_RADIO15, &CMapTool::OnOptionChange)


END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.

void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	int	iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 1. ��ӵ� ������ ��Ÿ���� ���� ������ ����ü�� �����ϱ� ���� �ڵ�
	// 2. ������ �ε����� ����. -1�� �����ϸ� �Լ��� ��ȯ ������ �巡�� �� ��ӵ� ������ ���� ��ȯ
	// 3. ����� ���ϸ��� �ݳ��ϴ� ������ �����͸� ����
	// 4. ������ ���� ������ 

	TCHAR	szFullPath[MAX_PATH] = L"";
	CFileInfo		FileInfo;

	for(int i = 0; i < iFileNumber; ++i)
	{
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);
		wstring	wstrRelativePath = FileInfo.ConvertRelativePath(szFullPath);
		CString strImageName	 = PathFindFileName(wstrRelativePath.c_str());
		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());

		map<CString, CImage*>::iterator	iter = m_MapPngImage.find(strImageName);

		if(iter == m_MapPngImage.end())
		{
			CImage*		pPngImage = new CImage;

			pPngImage->Load(wstrRelativePath.c_str());
			m_MapPngImage.insert(make_pair(strImageName, pPngImage));
			m_ListBox.AddString(strImageName);
		}

	}

	HorizontalScroll();

	UpdateData(FALSE);
}

void CMapTool::HorizontalScroll(void)
{
		CString		strName;
		CSize		csize;	
		int			iDCX = 0;		// ����Ʈ�ڽ� ����� ���� dc x���̸� ����

		CDC*		pDC = m_ListBox.GetDC();

		for(int i = 0; i < m_ListBox.GetCount(); ++i) // ����Ʈ �ڽ��� ��� ���� ��ȯ 
		{
			m_ListBox.GetText(i, strName);
			csize = pDC->GetTextExtent(strName);	// ������ ũ�⸦ �ȼ� ũ��� ��ȯ

			if(csize.cx > iDCX)
				iDCX = csize.cx;
		}
		m_ListBox.ReleaseDC(pDC);

		if(m_ListBox.GetHorizontalExtent() < iDCX)
		{
			m_ListBox.SetHorizontalExtent(iDCX);
		}

}

void CMapTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CString		strSelectName;

	int		iSelectNumber = m_ListBox.GetCurSel();

	if(iSelectNumber < 0)
		return;

	m_ListBox.GetText(iSelectNumber, strSelectName);

	map<CString, CImage*>::iterator	iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_Picture.SetBitmap(*iter->second);

	int i = 0;

	

	for(i = 0; i < strSelectName.GetLength(); ++i)
	{
		if(isdigit(strSelectName[i]) != 0)		// ��ȯ���� 0�� ���� ���� ������ ���
			break;								// ��ȯ���� 0�� �ƴ� �洩�� ���� ������ ���
	}

	strSelectName.Delete(0, i);
	m_iDrawID = _tstoi(strSelectName);	// ���ڿ��� ������ �����ͷ� �ٲ��ִ� �����ڵ� ��� �Լ�

	UpdateData(FALSE);
}

void CMapTool::OnSaveButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog		Dlg(FALSE, L"dat", L"*.dat", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"*.dat", this);

	// 1. ���� ��� ���� 2. ������ Ȯ���ڸ� 3. ���ʿ� ��� �� ���ڿ� 
	// 4. �ߺ� ���� ó���� ���� �Ű� ���� 5. ���� ���Ŀ� ���� Ȯ���ڸ�

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);

	SetCurrentDirectory(szDirPath);
	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �������ִ� �Լ�

	PathRemoveFileSpec(szDirPath);
	// ������ ��θ� ������ ��θ� �����ϴ� �Լ�

	lstrcat(szDirPath, L"..\\Data");


	Dlg.m_ofn.lpstrInitialDir = szDirPath;		// ��� ���

	CObj*		pBack = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBack;

	const vector<TILE*>*	pVecTile = ((CBack*)pBack)->GetTile();

	if(pVecTile == NULL)
		return;

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte;

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		WriteFile(hFile, (*pVecTile)[i], sizeof(TILE), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CMapTool::OnOptionChange()
{
	for(int i = 0; i < 15; ++i)
	{
		if(m_iRadio[i].GetCheck())
		{
			m_iState = i;
		}
	}
}