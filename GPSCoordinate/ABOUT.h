#pragma once
#include "afxwin.h"


// ABOUT �Ի���

class ABOUT : public CDialogEx
{
	DECLARE_DYNAMIC(ABOUT)

public:
	ABOUT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ABOUT();

	// �Ի�������
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
};
