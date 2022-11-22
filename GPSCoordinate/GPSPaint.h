#pragma once
#include "afxwin.h"
#include <GdiPlus.h>    
using namespace Gdiplus;

#define POINT_COUNT 100  

// GPSPaint 对话框

class GPSPaint : public CDialogEx
{
	DECLARE_DYNAMIC(GPSPaint)

	int   m_nzValues[POINT_COUNT];


	//绘制波形图
	void DrawWave(CDC* pDC, CRect& rectPicture);

	//绘制卫星图
	void DrawGPS(CDC* pDC, CRect& rectPicture);

	//双缓冲绘图   
	void Invalidate();

	void Draw(CDC* pDC);

public:
	GPSPaint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GPSPaint();

	// 对话框数据
	enum { IDD = IDD_GPSPaint };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	CStatic m_PictureControl;//picture control 控件变量
	CScrollBar m_ScrollBarH; //水平滚动条
	CScrollBar m_ScrollBarV; //垂直滚动条
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

