// Contrast1.cpp : 实现文件
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "GPSCoordinateDlg.h"
#include "GPS.h"
#include "Contrast1.h"
#include "afxdialogex.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#define N 10
using namespace std;


extern GPS gps[50];


// Contrast1 对话框

IMPLEMENT_DYNAMIC(Contrast1, CDialogEx)



Contrast1::Contrast1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Contrast1::IDD, pParent)
	, Edit1(_T(""))
{

}

Contrast1::~Contrast1()
{
}

void Contrast1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, db1);
	DDX_Text(pDX, IDC_EDIT1, Edit1);
	DDX_Control(pDX, IDC_LIST1, m_ListTem);
}


BEGIN_MESSAGE_MAP(Contrast1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Contrast1::OnBnClickedButton1)
	ON_COMMAND(ID_IGS, &Contrast1::OnIgs)
	ON_BN_CLICKED(IDCANCEL, &Contrast1::OnBnClickedCancel)
	ON_COMMAND(ID_saveigsfinal, &Contrast1::Onsaveigsfinal)
	ON_COMMAND(ID_exit2, &Contrast1::Onexit2)
	ON_BN_CLICKED(IDC_BUTTON2, &Contrast1::OnBnClickedButton2)
	ON_COMMAND(ID_saveonlywc, &Contrast1::Onsaveonlywc)
	ON_COMMAND(ID_BG2, &Contrast1::OnBg2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Contrast1::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// Contrast1 消息处理程序


void Contrast1::OnBnClickedButton1()
{
	if (isopen == 1)
	{
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		gpsnum = _ttoi(str);
		int state = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
		if (state == 1)
		{
			UpdateData(TRUE);
			if (Edit1.IsEmpty())
			{
				AfxMessageBox("未输入卫星号");
				return;
			}
			BOOL IsIGSTime = ISIGSTime(CGPSCoordinateDlg::f_minute, CGPSCoordinateDlg::f_second);
			if (IsIGSTime == TRUE)
			{
				ReadIGSFile(igsReadFilePathName, gpsnum, CGPSCoordinateDlg::f_year, CGPSCoordinateDlg::f_minute, CGPSCoordinateDlg::f_second);
				WCToIGS(gps, igps, em);
			}
			else
			{
				ArPoiPos(igps);
				WCToIGS(gps, igps, em);
			}
			CString str1, str2, str3;
			str1.Format(_T("%lf"), em[gpsnum].mx);
			str2.Format(_T("%lf"), em[gpsnum].my);
			str3.Format(_T("%lf"), em[gpsnum].mz);
			GetDlgItem(IDC_EDIT2)->SetWindowText(str1 + "," + str2 + "," + str3);
		}
		else
		{
			AfxMessageBox("复选框未选中，不能计算该卫星相对误差！");
		}
	}
	else
	{
		AfxMessageBox("请先打开文件！");
	}
}



void Contrast1::OnIgs()
{
	CFileDialog fileDlg(true, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("精密星历 (igs*.sp3)|igs*.sp3||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框  
	{
		igsReadFilePathName = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名  
		AfxMessageBox("IGS文件打开成功!");
		iscal = 0;
		isopen = 1;
	}
	else
	{
		AfxMessageBox("IGS文件打开失败!");
		isopen = 0;
	}
}


void Contrast1::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void Contrast1::Onsaveigsfinal()
{
	// TODO:  在此添加命令处理程序代码
	if (iscal == 0)
	{
		AfxMessageBox("请先计算所有卫星坐标误差！");
	}
	else
	{

		BOOL isOpen = FALSE;        //是否打开(否则为保存)  	
		CString filter = "文本文件 (*.txt)|*.txt||";   //文件过虑的类型  
		CFileDialog openFileDlg(isOpen, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
		openFileDlg.GetOFN().lpstrInitialDir = "E:\\FileTest\\test.doc";
		INT_PTR result = openFileDlg.DoModal();
		if (result == IDOK) {
			wcWriteFilePathName = openFileDlg.GetPathName();
		}
		else
		{
			AfxMessageBox("保存失败!");
			return;
		}

		BOOL iswrite;
		iswrite = WriteWCFile(wcWriteFilePathName, gps, igps, em);
		if (iswrite == TRUE)
		{
			AfxMessageBox("结果已保存!");

		}
	}
}


void Contrast1::Onexit2()
{
	if (IDNO == ::MessageBox(this->m_hWnd, _T("退出前请保存数据，否则不可恢复，退出吗?"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO))
	{
		return;
	}
	else {

		this->SendMessage(WM_CLOSE);
	}
}


void Contrast1::OnBnClickedButton2()
{
	if (isopen == 1)
	{
		int state = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
		if (state == 0)
		{
			BOOL IsIGSTime = ISIGSTime(CGPSCoordinateDlg::f_minute, CGPSCoordinateDlg::f_second);
			if (IsIGSTime == TRUE)
			{
				int i = 0;
				for (i = 1; i <= 32; i++)
				{
					ReadIGSFile(igsReadFilePathName, i, CGPSCoordinateDlg::f_year, CGPSCoordinateDlg::f_minute, CGPSCoordinateDlg::f_second);
				}
				WCToIGS(gps, igps, em);
			}

			else
			{
				ArPoiPos(igps);
				WCToIGS(gps, igps, em);
			}
			iscal = 1;
			AfxMessageBox("所有卫星计算完成，请保存结果！");
			//输入表格中的数据
			int j = 0;
			for (j = 1; j <= 32; j++)
			{
				int i = m_ListTem.GetItemCount();//获取list里面有多少行  
				CString ttt;
				ttt.Format("%d", i);
				CString str0;
				CString str1;
				CString str2;
				CString str3;
				CString str4;
				CString str5;
				CString str6;
				str0.Format(_T("%d"), gps[j].prn);
				str1.Format(_T("%lf"), gps[j].X);
				str2.Format(_T("%lf"), gps[j].Y);
				str3.Format(_T("%lf"), gps[j].Z);
				str4.Format(_T("%lf"), em[j].mx);
				str5.Format(_T("%lf"), em[j].my);
				str6.Format(_T("%lf"), em[j].mz);
				m_ListTem.InsertItem(i, ttt); //开辟一个行，并且设置行的内容为i的内容
				m_ListTem.SetItemText(i, 0, str0);//i代指在第几行插入数据，第二个参数代指第几列，第三个参数代指插入数据的值  
				m_ListTem.SetItemText(i, 1, str1);
				m_ListTem.SetItemText(i, 2, str2);
				m_ListTem.SetItemText(i, 3, str3);
				m_ListTem.SetItemText(i, 4, str4);
				m_ListTem.SetItemText(i, 5, str5);
				m_ListTem.SetItemText(i, 6, str6);
			}
		}
		else
		{
			AfxMessageBox("复选框选中后不能计算所有卫星！");
		}
	}
	else
	{
		AfxMessageBox("请先打开文件！");
	}
}

BOOL Contrast1::ReadIGSFile(CString FilePath, int prn, int hour, int minute, double second)
{
	BOOL IsFind = FALSE;
	BOOL IsIGSTime;
	DaFun DF;
	IsIGSTime = ISIGSTime(minute, second);
	CString strLine;
	///定义读取的参数
	int GPSNum;
	int i = 0;
	int j = 0;

	//临时参数
	CStdioFile OFile;
	//打开星历文件
	BOOL yesno = OFile.Open(FilePath, CFile::modeRead);
	if (yesno == FALSE)
	{
		AfxMessageBox("IGS文件打开错误!");
		return FALSE;
	}
	//读文件头,直接跳过
	do {
		yesno = OFile.ReadString(strLine);
		i++;
	} while (i < 23);

	//读数据变量
	double vt1 = 0, vt2 = 0;
	int t_year = 0, t_month = 0, t_day = 0, t_hour = 0, t_minute = 0;
	double t_second = 0;
	double t_c0 = 0, t_c1 = 0, t_c2 = 0;

	char temp[30] = { '\0' };
	char oneLine[100] = { '\0' };
	char temp2[30] = { '\0' };
	char oneLine2[100] = { '\0' };


	//判断打开文件时间是否正确
	strncpy_s(oneLine2, (LPCTSTR)strLine, sizeof(oneLine2));
	DF.cpstr(temp2, oneLine2, 3, 6, sizeof(temp2));
	t_year = _ttoi(temp2);
	if (t_year >= 2000)
	{
		t_year -= 2000;
	}
	if (t_year >= 1980 && t_year < 2000)
	{
		t_year -= 1980;
	}
	DF.cpstr(temp2, oneLine2, 8, 9, sizeof(temp2));
	t_month = _ttoi(temp2);
	DF.cpstr(temp2, oneLine2, 11, 12, sizeof(temp2));
	t_day = _ttoi(temp2);

	if (CGPSCoordinateDlg::f_year == t_year && CGPSCoordinateDlg::f_month == t_month && CGPSCoordinateDlg::f_day == t_day)
	{
	}
	else
	{
		MessageBox("打开文件时间错误，请检查！");
		return FALSE;
	}

	while (yesno)
	{
		DF.cpstr(temp2, oneLine2, 14, 16, sizeof(temp2));
		t_hour = _ttoi(temp2);
		DF.cpstr(temp2, oneLine2, 17, 19, sizeof(temp2));
		t_minute = _ttoi(temp2);
		DF.cpstr(temp2, oneLine2, 21, 31, sizeof(temp2));
		t_second = atof(temp2);
		//如果是给定时间	
		if (IsIGSTime == TRUE)
		{
			if (CGPSCoordinateDlg::f_hour == t_hour && CGPSCoordinateDlg::f_minute == t_minute && CGPSCoordinateDlg::f_second == t_second)
			{
				string str1;
				yesno = OFile.ReadString(strLine);
				do
				{
					strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
					DF.cpstr(temp2, oneLine2, 0, 2, sizeof(temp2));
					str1 = temp2;
					DF.cpstr(temp, oneLine, 2, 3, sizeof(temp));
					GPSNum = _ttoi(temp);

					if (GPSNum == prn)
					{
						IsFind = TRUE;///找到星		
						//	广播轨道-0
						strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
						DF.cpstr(temp, oneLine, 5, 18, sizeof(temp));
						igps[prn].X = atof(temp);
						DF.cpstr(temp, oneLine, 19, 32, sizeof(temp));
						igps[prn].Y = atof(temp);
						DF.cpstr(temp, oneLine, 33, 46, sizeof(temp));
						igps[prn].Z = atof(temp);
						IsFind = TRUE;
						OFile.Close();
						return IsFind;
					}
					else
					{
						IsFind = FALSE;
					}

				} while (str1 != "*  " && str1 != "EOF");
			}
			else
			{
				string str2;
				do
				{
					yesno = OFile.ReadString(strLine);
					strncpy_s(oneLine2, (LPCTSTR)strLine, sizeof(oneLine2));
					DF.cpstr(temp2, oneLine2, 0, 2, sizeof(temp2));
					str2 = temp2;
				} while (str2 != "*  " && str2 != "EOF");
				IsFind = FALSE;

				DF.cpstr(temp2, oneLine2, 14, 16, sizeof(temp2));
				t_hour = _ttoi(temp2);
				DF.cpstr(temp2, oneLine2, 17, 19, sizeof(temp2));
				t_minute = _ttoi(temp2);
				DF.cpstr(temp2, oneLine2, 21, 31, sizeof(temp2));
				t_second = atof(temp2);
			}
		}

	}
	OFile.Close();
	return IsFind;
}


//判断所求时间是不是IGS给定时间
BOOL Contrast1::ISIGSTime(int minute, double second)
{
	BOOL is = FALSE;
	if (second > 0)//秒数不是零秒肯定不是
	{
		is = FALSE;
	}
	else if (minute % 15 != 0)//分钟不是15的倍数肯定也不是
	{
		is = FALSE;
	}
	else
	{
		is = TRUE;
	}
	return is;
}

//求相对于IGS的误差
void Contrast1::WCToIGS(GPS* gps, IGPS* igps, EM* em)
{
	int i = 0;

	int state = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	if (state == 1)
	{
		em[gpsnum].mx = (gps[gpsnum].X - igps[gpsnum].X) * 1000;
		em[gpsnum].my = (gps[gpsnum].Y - igps[gpsnum].Y) * 1000;
		em[gpsnum].mz = (gps[gpsnum].Z - igps[gpsnum].Z) * 1000;
	}
	else
	{
		for (i = 1; i <= 32; i++)
		{
			if (gps[i].X == 0)
			{
				CString str;
				str.Format(_T("%d"), i);
				AfxMessageBox(str + "号卫星未找到！");
			}
			else
			{
				em[i].mx = (gps[i].X - igps[i].X) * 1000;
				em[i].my = (gps[i].Y - igps[i].Y) * 1000;
				em[i].mz = (gps[i].Z - igps[i].Z) * 1000;
			}
		}
	}

}


//写坐标+误差文件
BOOL Contrast1::WriteWCFile(CString FilePath, GPS* gps, IGPS* igps, EM* em)
{
	// TODO:  在此添加命令处理程序代码
	BOOL iswrite = TRUE;
	CStdioFile OFile;
	CFileException fileException;
	//打开星历文件
	OFile.Open(FilePath, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate, &fileException);

	OFile.WriteString(_T("卫星号，X(km),Y(km),Z(km),mx(m),my(m),mz(m)"));

	for (int i = 1; i <= 32; i++)
	{
		OFile.WriteString("\n");
		CString str;
		str.Format(_T("%d"), gps[i].prn);
		OFile.WriteString("PG" + str + ",");
		str.Format(_T("%lf"), gps[i].X);
		OFile.WriteString(str + ",");
		str.Format(_T("%lf"), gps[i].Y);
		OFile.WriteString(str + ",");
		str.Format(_T("%lf"), gps[i].Z);
		OFile.WriteString(str + ",");
		str.Format(_T("%lf"), em[i].mx);
		OFile.WriteString(str + ",");
		str.Format(_T("%lf"), em[i].my);
		OFile.WriteString(str + ",");
		str.Format(_T("%lf"), em[i].mz);
		OFile.WriteString(str);
	}
	OFile.Close();


	return iswrite;
}

BOOL Contrast1::WriteOnlyWCFile(CString FilePath, GPS* gps, IGPS* igps, EM* em)
{
	// TODO:  在此添加命令处理程序代码
	BOOL iswrite = TRUE;
	CStdioFile OFile;
	CFileException fileException;

	OFile.Open(FilePath, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate, &fileException);


	OFile.WriteString(_T("卫星号,mx(m),my(m),mz(m)"));

	for (int i = 1; i <= 32; i++)
	{
		OFile.WriteString("\n");
		CString str;
		str.Format(_T("%d"), gps[i].prn);
		OFile.WriteString("PG" + str + ",");
		str.Format(_T("%lf"), em[i].mx);
		OFile.WriteString(str + ",");
		str.Format(_T("%lf"), em[i].my);
		OFile.WriteString(str + ",");
		str.Format(_T("%lf"), em[i].mz);
		OFile.WriteString(str);
	}
	OFile.Close();


	return iswrite;
}

void Contrast1::Onsaveonlywc()
{
	// TODO:  在此添加命令处理程序代码
	if (iscal == 0)
	{
		AfxMessageBox("请先计算所有卫星坐标误差！");
	}
	else
	{

		BOOL isOpen = FALSE;        //是否打开(否则为保存)  	
		CString filter = "文本文件 (*.txt)|*.txt||";   //文件过虑的类型  
		CFileDialog openFileDlg(isOpen, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
		openFileDlg.GetOFN().lpstrInitialDir = "E:\\FileTest\\test.doc";
		INT_PTR result = openFileDlg.DoModal();
		if (result == IDOK) {
			wcWriteFilePathName = openFileDlg.GetPathName();
		}
		else
		{
			AfxMessageBox("保存失败!");
			return;
		}

		BOOL iswrite;
		iswrite = WriteOnlyWCFile(wcWriteFilePathName, gps, igps, em);
		if (iswrite == TRUE)
		{
			AfxMessageBox("结果已保存!");

		}
	}
}

//拉格朗日内插11
double Contrast1::lagrange(int bztime[N], double pos[N], int sqtime)
{
	int n = 11;//11阶内插
	double p, sqpos;
	int i, k;
	sqpos = 0.0;
	for (k = 0; k < n; k++)
	{
		p = 1.0;
		for (i = 0; i < n; i++)
			if (i != k)
			{

				p = p * (sqtime - bztime[i]) / (bztime[k] - bztime[i]);

			}
		sqpos += (p * pos[k]);

	}
	return sqpos;
}

//求任意点坐标
void Contrast1::ArPoiPos(IGPS* igps)
{
	string line;
	fstream iofile(igsReadFilePathName, ios::in | ios::out | ios::binary);
	if (!iofile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	int math;//
	double t = CGPSCoordinateDlg::f_hour * 3600 + CGPSCoordinateDlg::f_minute * 60 + CGPSCoordinateDlg::f_second;
	for (int i = 0; i < 2; i++)//取第n行数据，则i<n-1
	{
		getline(iofile, line);
	}
	getline(iofile, line);

	basic_string<char>line1 = line.substr(4, 2);
	int sat = atoi(line1.c_str());//sat为卫星数
	for (int i = 0; i < 19; i++)//取第n行数据，则i<n-4
	{
		getline(iofile, line);
	}
	int year[96], mouth[96], day[96], hour[96], min[96];
	basic_string<char>line2, line3, line4, line5, linet;
	for (int h = 0; h < 96; h++)//读取历元的年月日
	{
		getline(iofile, line);
		line1 = line.substr(3, 4);
		year[h] = atoi(line1.c_str());
		line2 = line.substr(8, 2);
		mouth[h] = atoi(line2.c_str());
		line3 = line.substr(11, 2);
		day[h] = atoi(line3.c_str());
		line4 = line.substr(14, 2);
		hour[h] = atoi(line4.c_str());
		line5 = line.substr(17, 2);
		min[h] = atoi(line5.c_str());
		for (int g = 0; g < sat; g++)//读取历元的各个卫星位置
		{
			int gn;
			getline(iofile, line);
			linet = line.substr(2, 2);
			gn = atoi(linet.c_str());
			line1 = line.substr(4, 14);
			num[h][gn][0] = atof(line1.c_str());
			line2 = line.substr(18, 14);
			num[h][gn][1] = atof(line2.c_str());
			line3 = line.substr(32, 14);
			num[h][gn][2] = atof(line3.c_str());
		}
	}
	int gps[96];
	for (int w = 0; w < 96; w++)
		gps[w] = hour[w] * 3600 + min[w] * 60;
	int time[11]; double xx[11], yy[11], zz[11];
	if (t <= 5400)
	{
		math = 0;
		for (int i = 0; i < 11; i++)
		{
			time[i] = gps[i];
		}
	}
	else if (t >= 81000)
	{
		math = 84;
		for (int i = 0; i < 11; i++)
		{
			time[i] = gps[i + 84];
		}
	}
	else for (int i = 0, count = 0; i < 96; i++)
	{
		if (t > gps[i])
		{
			count++;
		}
		else for (int j = 0; j < 11; j++)
			time[j] = gps[count - 5 + j];
		math = count - 5;
	}

	double xxx[11], yyy[11], zzz[11];
	for (int j = 1, coun = 1; j <= 32; j++, coun++)
	{
		if (num[math][j][0] == 0)
		{
			CString str;
			str.Format(_T("%d"), j);
			AfxMessageBox(str + "号卫星未找到！");
			continue;
		}
		for (int m = math, i = 0; m < math + 11; m++, i++)
		{
			xxx[i] = num[m][j][0];
			yyy[i] = num[m][j][1];
			zzz[i] = num[m][j][2];
		}
		double a = lagrange(time, xxx, t);
		double b = lagrange(time, yyy, t);
		double c = lagrange(time, zzz, t);
		igps[j].prn = j;
		igps[j].X = a;
		igps[j].Y = b;
		igps[j].Z = c;
	}

	iofile.close();
}


void Contrast1::OnBg2()
{
	// TODO:  在此添加命令处理程序代码

}


void Contrast1::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL Contrast1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置表格的表头
	CRect rect;
	m_ListTem.GetClientRect(&rect);
	int iLength = rect.Width();
	m_ListTem.SetExtendedStyle(m_ListTem.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListTem.InsertColumn(0, _T("卫星号"), LVCFMT_CENTER, 60);
	m_ListTem.InsertColumn(1, _T("X(km)"), LVCFMT_CENTER, (iLength - 60) / 6);
	m_ListTem.InsertColumn(2, _T("Y(km)"), LVCFMT_CENTER, (iLength - 60) / 6);
	m_ListTem.InsertColumn(3, _T("Z(km)"), LVCFMT_CENTER, (iLength - 60) / 6);
	m_ListTem.InsertColumn(4, _T("mx(m)"), LVCFMT_CENTER, (iLength - 60) / 6);
	m_ListTem.InsertColumn(5, _T("my(m)"), LVCFMT_CENTER, (iLength - 60) / 6);
	m_ListTem.InsertColumn(6, _T("mz(m)"), LVCFMT_CENTER, (iLength - 60) / 6);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
