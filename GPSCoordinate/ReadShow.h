#pragma once


// ReadShow 对话框

class ReadShow : public CDialogEx
{
	DECLARE_DYNAMIC(ReadShow)

public:
	ReadShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ReadShow();

	// 对话框数据
	enum { IDD = IDD_READ1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


