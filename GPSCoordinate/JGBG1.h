#pragma once
#include "afxcmn.h"


// JGBG1 �Ի���

class JGBG1 : public CDialogEx
{
	DECLARE_DYNAMIC(JGBG1)

public:
	JGBG1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~JGBG1();

	// �Ի�������
	enum { IDD = IDD_JGBG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListTem;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};

