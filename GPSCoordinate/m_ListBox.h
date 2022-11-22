#pragma once


// m_ListBox 对话框

class m_ListBox : public CDialogEx
{
	DECLARE_DYNAMIC(m_ListBox)

public:
	m_ListBox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~m_ListBox();

	// 对话框数据
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

