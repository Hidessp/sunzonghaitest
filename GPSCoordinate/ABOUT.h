#pragma once
#include "afxwin.h"


// ABOUT 对话框

class ABOUT : public CDialogEx
{
	DECLARE_DYNAMIC(ABOUT)

public:
	ABOUT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ABOUT();

	// 对话框数据
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
};
