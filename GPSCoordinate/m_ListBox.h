#pragma once


// m_ListBox �Ի���

class m_ListBox : public CDialogEx
{
	DECLARE_DYNAMIC(m_ListBox)

public:
	m_ListBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_ListBox();

	// �Ի�������
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

