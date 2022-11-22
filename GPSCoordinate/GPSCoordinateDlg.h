// GPSCoordinateDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "DaFun.h"
#include"GPS.h"
#include "NumberEdit.h"  

// CGPSCoordinateDlg 对话框
class CGPSCoordinateDlg : public CDialogEx
{
	// 构造
public:
	CGPSCoordinateDlg(CWnd* pParent = NULL);	// 标准构造函数
	CMenu m_Menu;//定义菜单

// 对话框数据
	enum { IDD = IDD_GPSCOORDINATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_title;
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnRead1();



	//导航文件内容
private:
	//第一行数据
	int m_PRN;
	int	m_year;
	int	m_month;
	int	m_day;
	int	m_hour;
	int	m_minute;
	double	m_second;
	double	m_c0;
	double	m_c1;
	double	m_c2;


	//星历参数
	double m_toe;//星历表参考历元
	double m_toc;//卫星钟参考时刻
	double m_tow;//GPS星期秒数
	int m_IODE;//星历表数据龄期
	double m_M0;//按参考历元toe计算的平近点角（弧度）
	double m_Det_n;//由精密星历计算得到的卫星平均角速度与按给定参数计算所得的平均角速度之差（弧度/秒）
	double m_e;//轨道偏心率
	double m_sqrt_a;//轨道长半径的平方根（0.5m）
	double m_OM0;//按参考历元toe计算的升交点赤径（弧度）
	double m_i0;//按参考历元toe计算的轨道倾角（弧度）
	double m_omega;//近地点角距（弧度）
	double m_OM;//升交点赤径的变化率（弧度/秒）
	double m_I;//轨道倾角变化率（弧度/秒）
	double m_Cuc;//纬度幅角的余弦调和改正的振幅（弧度）
	double m_Cus;//纬度幅角的正弦调和改正的振幅（弧度）
	double m_Crc;//轨道半径的余弦调和项改正的振幅（m）
	double m_Crs;//轨道半径的正弦调和项改正的振幅（m）
	double m_Cic;//轨道倾角的余弦调和项改正的振幅（弧度）
	double m_Cis;//轨道倾角的正弦调和项改正的振幅（弧度）
	int m_GPD;//周数（周）
	double m_Tgd;//载波L1、L2的电离层时延迟差（秒）
	double m_IODC;//星钟的数据龄期
	double m_a0, m_a1, m_a2;/*卫星钟差（秒）－ 时间偏差,卫星钟速（秒/秒）－ 频率偏差系数
							卫星钟速变率（秒/秒2）－ 漂移系数*/
	double m_L2;
	double m_GpsWk;
	double m_L2p;

	double m_SatPrecisn;
	double m_SatHealth;
	double m_TGD;


	double m_T;
	double m_area;
	double m_unknow1;
	double m_unknow2;

public:
	//要求的时刻和卫星号
	static	int f_year;
	static	int f_month;
	static	int f_day;
	static	int f_hour;
	static	int f_minute;
	static	double f_second;
	static	int f_GPSNO;
	static	double gpst;//GPS时间

private:
	CString gReadFilePathName;//打开文件的路径
	CString gWriteFilePathName;//打开文件的路径
	int iscal2;
	int isopen;
	CNumberEdit NumberEdit1;


	//计算函数
	//从年 月 日 转换为GPS时间
	int GetGPSTime(int year, int month, int day, int hour, int minute, double second, double& gpstime);
	BOOL ComputStar();

	//计算卫星位置
	BOOL GetGPSPos(int prn, double& X, double& Y, double& Z);

	//读取导航文件
	BOOL ReadOFile(CString FilePath, int prn, int hour, int minute, double second);

	//写卫星坐标文件txt
	BOOL WritePosFile(CString FilePath, GPS gps[]);

	//计算两个时间相减所得秒数
	double TwoTimeMin(int h1, int m1, double s1, int h2, int m2, double s2);

	//判断一个月有多少天
	int GetDaysInMonth(int y, int m);

public:
	afx_msg void OnOpengbxl();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnContrast1();
	afx_msg void OnGpspos();
	CButton OneGPS;
	afx_msg void OnEnChangeEdit12();
	CEdit onegpsy;
	CEdit onegpsx;
	CEdit onegpsz;
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void Onigsfinal();
	afx_msg void OnExit1();
	afx_msg void Onsaveonlywc();
	CString Edit3;
	CString Edit4;
	CString Edit5;
	CString Edit6;
	CString Edit7;
	CString Edit8;
	CString Edit9;
	afx_msg void OnBg1();
	afx_msg void OnAbout();
	afx_msg void On32804();
	afx_msg void OnInstruction();
};


