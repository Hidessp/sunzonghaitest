#pragma once
#include "afxcmn.h"


// JGBG1 对话框

class JGBG1 : public CDialogEx
{
	DECLARE_DYNAMIC(JGBG1)

public:
	JGBG1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~JGBG1();

	// 对话框数据
	enum { IDD = IDD_JGBG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListTem;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};

