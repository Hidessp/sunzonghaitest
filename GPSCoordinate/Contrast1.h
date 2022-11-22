/**************************************************************************
*  @Copyright (c) 2018, QGM, All rights reserved.

*  @file     : NumberEdit.h
*  @version  : ver 1.0

*  @author   : 邵沛涵
*  @Creation : 2018/4/3 12:44:25
*  @Modification : 2018/4/6 20:24:09
*  @describe : 读入sp3文件，对比计算精度，并输入txt文件。
*  @modify   : 无

**************************************************************************/
#pragma once
#include "afxwin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "afxcmn.h"
#define N 10
using namespace std;


// Contrast1 对话框

class Contrast1 : public CDialogEx
{
	DECLARE_DYNAMIC(Contrast1)

public:
	Contrast1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Contrast1();

	// 对话框数据
	enum { IDD = IDD_CONTRAST1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton db1;
	afx_msg void OnIgs();

private:
	int gpsnum;
	int iscal;
	int isopen;
	CString igsReadFilePathName;
	CString wcWriteFilePathName;

	double m[50];
	double num[96][100][3];//一天96组观测数据，至多一百颗卫星的xyz值

public:
	typedef  struct EVERYM
	{
		//EVERYM();
		//~EVERYM();
		double mx;
		double my;
		double mz;
	}EM;

	EM em[50];

private:
	typedef struct IGSGPS
	{
		//IGSGPS();
		//~IGSGPS();
		int prn = 0;
		double X = 0;
		double Y = 0;
		double Z = 0;

	}IGPS;

	IGPS igps[50];

	//读取IGS最终星历文件
	BOOL ReadIGSFile(CString FilePath, int prn, int hour, int minute, double second);
	//写坐标+误差
	BOOL WriteWCFile(CString FilePath, GPS* gps, IGPS* igps, EM* em);
	//只写误差
	BOOL WriteOnlyWCFile(CString FilePath, GPS* gps, IGPS* igps, EM* em);
	//判断所求时间是不是IGS给定时间
	BOOL ISIGSTime(int minute, double second);
	//拉格朗日内插法
	double lagrange(int bztime[N], double pos[N], int sqtime);
	//求相对于IGS的误差
	void WCToIGS(GPS* gps, IGPS* igps, EM* em);
	//计算任意点坐标
	void ArPoiPos(IGPS* igps);
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void Onsaveigsfinal();
	afx_msg void Onexit2();
	afx_msg void OnBnClickedButton2();
	afx_msg void Onsaveonlywc();
	CString Edit1;
	afx_msg void OnBg2();
	CListCtrl m_ListTem;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};

