// JGBG1.cpp : 实现文件
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "JGBG1.h"
#include "GPS.h"
#include "Contrast1.h"
#include "afxdialogex.h"


// JGBG1 对话框
extern GPS gps[50];

IMPLEMENT_DYNAMIC(JGBG1, CDialogEx)

JGBG1::JGBG1(CWnd* pParent /*=NULL*/)
	: CDialogEx(JGBG1::IDD, pParent)
{

}

JGBG1::~JGBG1()
{
}

void JGBG1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListTem);
}


BEGIN_MESSAGE_MAP(JGBG1, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &JGBG1::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// JGBG1 消息处理程序


void JGBG1::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL JGBG1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置表格的表头
	CRect rect;
	m_ListTem.GetClientRect(&rect);
	int iLength = rect.Width();
	m_ListTem.SetExtendedStyle(m_ListTem.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListTem.InsertColumn(0, _T("卫星号"), LVCFMT_CENTER, 60);
	m_ListTem.InsertColumn(1, _T("X(km)"), LVCFMT_CENTER, (iLength - 60) / 3);
	m_ListTem.InsertColumn(2, _T("Y(km)"), LVCFMT_CENTER, (iLength - 60) / 3);
	m_ListTem.InsertColumn(3, _T("Z(km)"), LVCFMT_CENTER, (iLength - 60) / 3);

	//输入表格中的数据
	int j = 0;
	for (j = 1; j <= 32; j++)
	{
		int i = m_ListTem.GetItemCount();//获取list里面有多少行  
		CString ttt;
		ttt.Format("%d", i);
		CString str0;
		CString str1;
		CString str2;
		CString str3;
		str0.Format(_T("%d"), gps[j].prn);
		str1.Format(_T("%lf"), gps[j].X);
		str2.Format(_T("%lf"), gps[j].Y);
		str3.Format(_T("%lf"), gps[j].Z);
		m_ListTem.InsertItem(i, ttt); //开辟一个行，并且设置行的内容为i的内容
		m_ListTem.SetItemText(i, 0, str0);
		m_ListTem.SetItemText(i, 1, str1);//i代指在第几行插入数据，第二个参数代指第几列，第三个参数代指插入数据的值  
		m_ListTem.SetItemText(i, 2, str2);
		m_ListTem.SetItemText(i, 3, str3);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
