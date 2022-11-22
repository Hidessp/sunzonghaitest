#pragma once
#include "afxwin.h"
#include <GdiPlus.h>    
using namespace Gdiplus;

#define POINT_COUNT 100  

// GPSPaint �Ի���

class GPSPaint : public CDialogEx
{
	DECLARE_DYNAMIC(GPSPaint)

	int   m_nzValues[POINT_COUNT];


	//���Ʋ���ͼ
	void DrawWave(CDC* pDC, CRect& rectPicture);

	//��������ͼ
	void DrawGPS(CDC* pDC, CRect& rectPicture);

	//˫�����ͼ   
	void Invalidate();

	void Draw(CDC* pDC);

public:
	GPSPaint(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GPSPaint();

	// �Ի�������
	enum { IDD = IDD_GPSPaint };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_picDraw;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

private:
	CString m_strFilePath;

	REAL m_zoom;
	CRect m_Rect;

	REAL m_imgX;
	REAL m_imgY;

	PointF m_PtStart;
	PointF m_mouseDown;
	bool m_mousepressed;


	CImage m_pic;
	CDC m_cacheDC;
	CDC* m_picDC;
	CBitmap m_cacheBitmap;

	CRect m_client;
	int m_iFirst;

	int m_picWidth;
	int m_picHeight;

	int m_iShowWidth;
	int m_iShowHeight;

	int m_iX;
	int m_iY;

public:
	CStatic m_PictureControl;//picture control �ؼ�����
	CScrollBar m_ScrollBarH; //ˮƽ������
	CScrollBar m_ScrollBarV; //��ֱ������
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar m_hScrollBar;
	CScrollBar m_vScrollBar;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

