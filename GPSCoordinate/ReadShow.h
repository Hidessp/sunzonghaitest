#pragma once


// ReadShow �Ի���

class ReadShow : public CDialogEx
{
	DECLARE_DYNAMIC(ReadShow)

public:
	ReadShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ReadShow();

	// �Ի�������
	enum { IDD = IDD_READ1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


