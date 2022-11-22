// m_ListBox.cpp : 实现文件
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "m_ListBox.h"
#include "afxdialogex.h"


// m_ListBox 对话框

IMPLEMENT_DYNAMIC(m_ListBox, CDialogEx)

m_ListBox::m_ListBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(m_ListBox::IDD, pParent)
{

}

m_ListBox::~m_ListBox()
{
}

void m_ListBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(m_ListBox, CDialogEx)
END_MESSAGE_MAP()


// m_ListBox 消息处理程序
