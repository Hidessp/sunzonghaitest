// ABOUT.cpp : ʵ���ļ�
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "ABOUT.h"
#include "afxdialogex.h"


// ABOUT �Ի���

IMPLEMENT_DYNAMIC(ABOUT, CDialogEx)

ABOUT::ABOUT(CWnd* pParent /*=NULL*/)
	: CDialogEx(ABOUT::IDD, pParent)
{

}

ABOUT::~ABOUT()
{
}

void ABOUT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(ABOUT, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &ABOUT::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// ABOUT ��Ϣ�������


void ABOUT::OnLbnSelchangeList1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL ABOUT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������
	CFont* font;
	LOGFONT stFont;
	font = new CFont;
	font->CreatePointFont(150, (LPCTSTR)_T("����_GB2312"));
	font->GetLogFont(&stFont);
	font->DeleteObject();
	GetDlgItem(IDC_LIST1)->SetFont(font, true);
	//*********************


	m_ListBox.AddString(_T("GPS��������������"));
	m_ListBox.AddString(_T(""));
	m_ListBox.AddString(_T("���ߣ�21320111"));
	m_ListBox.AddString(_T("�汾�ţ�v1.0"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
