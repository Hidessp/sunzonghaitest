// ABOUT.cpp : 实现文件
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "ABOUT.h"
#include "afxdialogex.h"


// ABOUT 对话框

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


// ABOUT 消息处理程序


void ABOUT::OnLbnSelchangeList1()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL ABOUT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置字体
	CFont* font;
	LOGFONT stFont;
	font = new CFont;
	font->CreatePointFont(150, (LPCTSTR)_T("楷体_GB2312"));
	font->GetLogFont(&stFont);
	font->DeleteObject();
	GetDlgItem(IDC_LIST1)->SetFont(font, true);
	//*********************


	m_ListBox.AddString(_T("GPS卫星坐标计算软件"));
	m_ListBox.AddString(_T(""));
	m_ListBox.AddString(_T("作者：21320111"));
	m_ListBox.AddString(_T("版本号：v1.0"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
