/**************************************************************************
*  @Copyright (c) 2018, QGM, All rights reserved.

*  @file     : NumberEdit.h
*  @version  : ver 1.0

*  @author   : ���溭
*  @Creation : 2018/4/3 12:44:25
*  @Modification : 2018/4/6 20:24:09
*  @describe : ����sp3�ļ����Աȼ��㾫�ȣ�������txt�ļ���
*  @modify   : ��

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


// Contrast1 �Ի���

class Contrast1 : public CDialogEx
{
	DECLARE_DYNAMIC(Contrast1)

public:
	Contrast1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Contrast1();

	// �Ի�������
	enum { IDD = IDD_CONTRAST1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	double num[96][100][3];//һ��96��۲����ݣ�����һ�ٿ����ǵ�xyzֵ

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

	//��ȡIGS���������ļ�
	BOOL ReadIGSFile(CString FilePath, int prn, int hour, int minute, double second);
	//д����+���
	BOOL WriteWCFile(CString FilePath, GPS* gps, IGPS* igps, EM* em);
	//ֻд���
	BOOL WriteOnlyWCFile(CString FilePath, GPS* gps, IGPS* igps, EM* em);
	//�ж�����ʱ���ǲ���IGS����ʱ��
	BOOL ISIGSTime(int minute, double second);
	//���������ڲ巨
	double lagrange(int bztime[N], double pos[N], int sqtime);
	//�������IGS�����
	void WCToIGS(GPS* gps, IGPS* igps, EM* em);
	//�������������
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

