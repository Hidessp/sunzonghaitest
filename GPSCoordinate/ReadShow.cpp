// ReadShow.cpp : ʵ���ļ�
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "ReadShow.h"
#include "afxdialogex.h"


// ReadShow �Ի���

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


// ReadShow ��Ϣ�������
