// ReadShow.cpp : 实现文件
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "ReadShow.h"
#include "afxdialogex.h"


// ReadShow 对话框

IMPLEMENT_DYNAMIC(ReadShow, CDialogEx)

ReadShow::ReadShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(ReadShow::IDD, pParent)
{

}

ReadShow::~ReadShow()
{
}

void ReadShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ReadShow, CDialogEx)
END_MESSAGE_MAP()


// ReadShow 消息处理程序
