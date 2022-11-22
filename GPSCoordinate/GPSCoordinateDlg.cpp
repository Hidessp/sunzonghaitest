
// GPSCoordinateDlg.cpp: 实现文件
//


#include "framework.h"
#include "GPSCoordinate.h"
#include "GPSCoordinateDlg.h"
#include "Contrast1.h"
#include "JGBG1.h"
#include "afxdialogex.h"
#include "GPS.h"
#include "Resource.h"
#include "ABOUT.h"
#include "GPSPaint.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 3.1415926535897932384626433832795

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
extern  GPS gps[50];

int CGPSCoordinateDlg::f_year = 0;
int CGPSCoordinateDlg::f_month = 0;
int CGPSCoordinateDlg::f_day = 0;
int CGPSCoordinateDlg::f_hour = 0;
int CGPSCoordinateDlg::f_minute = 0;
double CGPSCoordinateDlg::f_second = 0;
int CGPSCoordinateDlg::f_GPSNO = 0;
double CGPSCoordinateDlg::gpst = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGPSCoordinateDlg 对话框



CGPSCoordinateDlg::CGPSCoordinateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GPSCOORDINATE_DIALOG, pParent)
	, Edit3(_T(""))
	, Edit4(_T(""))
	, Edit5(_T(""))
	, Edit6(_T(""))
	, Edit7(_T(""))
	, Edit8(_T(""))
	, Edit9(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//绑定控件
void CGPSCoordinateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_title);
	DDX_Control(pDX, IDC_CHECK1, OneGPS);
	DDX_Control(pDX, IDC_EDIT12, onegpsy);
	DDX_Control(pDX, IDC_EDIT8, onegpsx);
	DDX_Control(pDX, IDC_EDIT11, onegpsz);
	DDX_Text(pDX, IDC_EDIT3, Edit3);
	DDX_Text(pDX, IDC_EDIT4, Edit4);
	DDX_Text(pDX, IDC_EDIT5, Edit5);
	DDX_Text(pDX, IDC_EDIT6, Edit6);
	DDX_Text(pDX, IDC_EDIT7, Edit7);
	DDX_Text(pDX, IDC_EDIT10, Edit8);
	DDX_Text(pDX, IDC_EDIT9, Edit9);

	//使“秒”控件只能输入数字和小数点
	DDX_Control(pDX, IDC_EDIT10, NumberEdit1);
}

BEGIN_MESSAGE_MAP(CGPSCoordinateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC1, &CGPSCoordinateDlg::OnStnClickedStatic1)
	ON_COMMAND(ID_READ1, &CGPSCoordinateDlg::OnRead1)
	ON_COMMAND(ID_OPENGBXL, &CGPSCoordinateDlg::OnOpengbxl)
	ON_BN_CLICKED(IDC_BUTTON1, &CGPSCoordinateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGPSCoordinateDlg::OnBnClickedButton2)
	ON_COMMAND(ID_Contrast1, &CGPSCoordinateDlg::OnContrast1)
	ON_COMMAND(ID_GPSPOS, &CGPSCoordinateDlg::OnGpspos)
	ON_EN_CHANGE(IDC_EDIT12, &CGPSCoordinateDlg::OnEnChangeEdit12)
	ON_STN_CLICKED(IDC_STATIC3, &CGPSCoordinateDlg::OnStnClickedStatic3)
	ON_WM_TIMER()
	ON_COMMAND(ID_igsfinal, &CGPSCoordinateDlg::Onigsfinal)
	ON_COMMAND(ID_EXIT1, &CGPSCoordinateDlg::OnExit1)
	ON_COMMAND(ID_saveonlywc, &CGPSCoordinateDlg::Onsaveonlywc)
	ON_COMMAND(ID_BG1, &CGPSCoordinateDlg::OnBg1)
	ON_COMMAND(ID_ABOUT, &CGPSCoordinateDlg::OnAbout)
	ON_COMMAND(ID_32804, &CGPSCoordinateDlg::On32804)
END_MESSAGE_MAP()

CFont m_Font;
// CGPSCoordinateDlg 消息处理程序

BOOL CGPSCoordinateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	SetTimer(1, 1000, NULL);

	// TODO: 在此添加额外的初始化代码
	// 
	//设置标题字体
	m_Font.CreatePointFont(200, "宋体", NULL);
	m_title.SetFont(&m_Font, true);
	//添加菜单
	m_Menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1
	SetMenu(&m_Menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGPSCoordinateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

//绘制
void CGPSCoordinateDlg::OnPaint()
{
	CFont   m_font;
	m_font.CreatePointFont(66, _T("Verdana   粗体"));
	GetDlgItem(IDC_STATIC17)->SetFont(&m_font);
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGPSCoordinateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGPSCoordinateDlg::OnStnClickedStatic1()
{
	// TODO:  在此添加控件通知处理程序代码
}

//打开比较窗口
void CGPSCoordinateDlg::OnRead1()
{
	// TODO:  在此添加命令处理程序代码
	Contrast1  Dlg1;
	Dlg1.DoModal();

}

//从年月日转换为GPS时间
int  CGPSCoordinateDlg::GetGPSTime(int year, int month, int day, int hour, int minute, double second, double& gpstime)
{
	int DayofMonth = 0;
	int DayofYear = 0;
	int weekno = 0;
	int dayofweek;
	int m;
	if (year < 1980 || month < 1 || month > 12 || day < 1 || day > 31)
		return weekno;

	///计算从1980年到当前的前一年的天数
	for (m = 1980; m < year; m++)
	{
		if ((m % 4 == 0 && m % 100 != 0) || (m % 400 == 0))
		{
			DayofYear += 366;
		}
		else
			DayofYear += 365;
	}
	///计算当前一年内从元月到当前前一月的天数
	for (m = 1; m < month; m++)
	{
		if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
			DayofMonth += 31;
		else if (m == 4 || m == 6 || m == 9 || m == 11)
			DayofMonth += 30;
		else if (m == 2)
		{
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				DayofMonth += 29;
			else
				DayofMonth += 28;

		}
	}
	DayofMonth = DayofMonth + day - 6;///加上当月天数/减去1980年元月的6日

	weekno = (DayofYear + DayofMonth) / 7;//计算GPS周
	dayofweek = (DayofYear + DayofMonth) % 7;
	//计算GPS时间
	gpstime = dayofweek * 86400 + hour * 3600 + minute * 60 + second;
	return weekno;
}

//读取N文件
BOOL CGPSCoordinateDlg::ReadOFile(CString FilePath, int prn, int hour, int minute, double second)
{
	BOOL IsFind;
	CString strLine;
	///定义读取的参数
	int GPSNum;
	int i;
	//临时参数
	CStdioFile OFile;
	//打开星历文件
	BOOL yesno = OFile.Open(FilePath, CFile::modeRead);
	if (yesno == FALSE)
	{
		AfxMessageBox("导航文件打开错误!");
		return FALSE;
	}
	//读文件头,直接跳过
	do {
		yesno = OFile.ReadString(strLine);
	} while (strLine.Find("                                                            END OF HEADER") != NULL);
	//读数据
	int ii = 0;
	int jj = 0;
	int kk = 0;
	double vt1 = 0, vt2 = 0;
	int t_hour = 0, t_minute = 0;
	double t_second = 0;
	double t_c0 = 0, t_c1 = 0, t_c2 = 0;
	while (yesno)
	{
		DaFun DF;
		//读取卫星号所在行
		yesno = OFile.ReadString(strLine);
		GPSNum = atoi(strLine.Left(2));

		//判断打开文件是否正确	
		if (ii == 0)
		{
			char temp2[30] = { '\0' };
			char oneLine2[100] = { '\0' };
			strncpy_s(oneLine2, (LPCTSTR)strLine, sizeof(oneLine2));
			DF.cpstr(temp2, oneLine2, 3, 4, sizeof(temp2));
			m_year = _ttoi(temp2);
			DF.cpstr(temp2, oneLine2, 6, 7, sizeof(temp2));
			m_month = _ttoi(temp2);
			DF.cpstr(temp2, oneLine2, 9, 10, sizeof(temp2));
			m_day = _ttoi(temp2);
			if (f_year == m_year && f_month == m_month && f_day == m_day)
			{
			}
			else
			{
				MessageBox("打开文件时间错误，请检查！");
				return FALSE;
			}
		}

		if (GPSNum == prn)
		{
			IsFind = TRUE;///找到星 
			kk = 1;
			char temp[30] = { '\0' };
			char oneLine[100] = { '\0' };


			//	广播轨道-0
			strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
			DF.cpstr(temp, oneLine, 0, 1, sizeof(temp));
			m_PRN = _ttoi(temp);
			DF.cpstr(temp, oneLine, 3, 4, sizeof(temp));
			m_year = _ttoi(temp);
			DF.cpstr(temp, oneLine, 6, 7, sizeof(temp));
			m_month = _ttoi(temp);
			DF.cpstr(temp, oneLine, 9, 10, sizeof(temp));
			m_day = _ttoi(temp);
			DF.cpstr(temp, oneLine, 12, 13, sizeof(temp));
			m_hour = _ttoi(temp);
			DF.cpstr(temp, oneLine, 15, 16, sizeof(temp));
			m_minute = _ttoi(temp);
			DF.cpstr(temp, oneLine, 17, 21, sizeof(temp));
			m_second = atof(temp);
			DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
			m_a0 = atof(temp);
			DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
			m_a1 = atof(temp);
			DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
			m_a2 = atof(temp);

			vt1 = TwoTimeMin(m_hour, m_minute, m_second, f_hour, f_minute, f_second);

			if (jj == 0)
			{
				t_hour = m_hour;
				t_minute = m_minute;
				t_second = m_second;
				vt2 = vt1;
			}

			if (abs(vt1) <= abs(vt2) && f_day == m_day)
			{
				vt2 = vt1;
				t_hour = m_hour;
				t_minute = m_minute;
				t_second = m_second;
				t_c0 = m_c0;
				t_c1 = m_c1;
				t_c2 = m_c2;

				yesno = OFile.ReadString(strLine);//	广播轨道-1
				strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
				DF.cpstr(temp, oneLine, 3, 21, sizeof(temp));
				m_IODE = atof(temp);
				DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
				m_Crs = atof(temp);
				DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
				m_Det_n = atof(temp);
				DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
				m_M0 = atof(temp);

				yesno = OFile.ReadString(strLine);//	广播轨道-2
				strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
				DF.cpstr(temp, oneLine, 3, 21, sizeof(temp));
				m_Cuc = atof(temp);
				DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
				m_e = atof(temp);
				DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
				m_Cus = atof(temp);
				DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
				m_sqrt_a = atof(temp);

				yesno = OFile.ReadString(strLine);//	广播轨道-3
				strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
				DF.cpstr(temp, oneLine, 3, 21, sizeof(temp));
				m_toe = atof(temp);
				DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
				m_Cic = atof(temp);
				DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
				m_OM0 = atof(temp);
				DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
				m_Cis = atof(temp);

				yesno = OFile.ReadString(strLine);//	广播轨道-4
				strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
				DF.cpstr(temp, oneLine, 3, 21, sizeof(temp));
				m_i0 = atof(temp);
				DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
				m_Crc = atof(temp);
				DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
				m_omega = atof(temp);
				DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
				m_OM = atof(temp);

				yesno = OFile.ReadString(strLine);//	广播轨道-5
				strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
				DF.cpstr(temp, oneLine, 3, 21, sizeof(temp));
				m_I = atof(temp);
				DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
				m_L2 = atof(temp);
				DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
				m_GpsWk = atof(temp);
				DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
				m_L2p = atof(temp);

				yesno = OFile.ReadString(strLine);//	广播轨道-6
				strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
				DF.cpstr(temp, oneLine, 3, 21, sizeof(temp));
				m_SatPrecisn = atof(temp);
				DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
				m_SatHealth = atof(temp);
				DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
				m_TGD = atof(temp);
				DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
				m_IODC = atof(temp);

				yesno = OFile.ReadString(strLine);//	广播轨道-7
				strncpy_s(oneLine, (LPCTSTR)strLine, sizeof(oneLine));
				DF.cpstr(temp, oneLine, 3, 21, sizeof(temp));
				m_T = atof(temp);
				DF.cpstr(temp, oneLine, 22, 40, sizeof(temp));
				m_area = atof(temp);
				DF.cpstr(temp, oneLine, 41, 59, sizeof(temp));
				m_unknow1 = atof(temp);
				DF.cpstr(temp, oneLine, 60, 78, sizeof(temp));
				m_unknow2 = atof(temp);
				//return;
			}
			else
			{
				for (i = 0; i < 7; i++)
					yesno = OFile.ReadString(strLine);

			}
			jj++;
		}
		else
		{
			for (i = 0; i < 7; i++)
				yesno = OFile.ReadString(strLine);
		}
		ii++;
	}
	m_hour = t_hour;
	m_minute = t_minute;
	m_second = t_second;
	m_c0 = t_c0;
	m_c1 = t_c1;
	m_c2 = t_c2;

	if (kk == 0)
	{
		IsFind = FALSE;
	}

	gps[prn].prn = prn;
	if (IsFind == TRUE)
	{
		GetGPSPos(gps[prn].prn, gps[prn].X, gps[prn].Y, gps[prn].Z);
	}

	OFile.Close();
	return IsFind;
}

//写坐标文件txt
BOOL CGPSCoordinateDlg::WritePosFile(CString FilePath, GPS gps[])
{
	BOOL IsFind = TRUE;

	CStdioFile OFile;
	CFileException fileException;
	//打开星历文件

	OFile.Open(FilePath, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate, &fileException);

	OFile.WriteString(_T("卫星号，X(km),Y(km),Z(km)"));

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
		OFile.WriteString(str);
	}
	OFile.Close();

	return IsFind;
}


//计算两个时间相减所得秒数
double CGPSCoordinateDlg::TwoTimeMin(int h1, int m1, double s1, int h2, int m2, double s2)
{
	double result = 0;
	double t1, t2;
	t1 = h1 * 3600 + m1 * 60 + s1;
	t2 = h2 * 3600 + m2 * 60 + s2;

	result = t1 - t2;
	return result;
}


////根据轨道参数，计算卫星位置
BOOL CGPSCoordinateDlg::GetGPSPos(int prn, double& X, double& Y, double& Z)
{
	double GM = 3.986005e+14;
	//double a = 6378137;
	double omg_e = 7.29211515e-5;
	double n, tk, Mk, Ek, Vk, PHIk, dt;
	double Cgam_u, Cgam_r, Cgam_i;
	double Mu_k, r_k, i_k;
	double xk, yk;
	double OMk;
	double atany, atanz;
	// 1、计算卫星运动的平均角速度n
	n = sqrt(GM) / (m_sqrt_a * m_sqrt_a * m_sqrt_a);
	n = n + m_Det_n;
	// 2、计算归化观测时间tk
	//首先是卫星钟差改正
	tk = gpst - m_toe;
	dt = m_a0 + m_a1 * tk + m_a2 * tk * tk;
	tk = tk - dt;
	if (tk > 302400)  tk -= 604800;
	if (tk < -302400) tk += 604800;
	// 3、观测时刻卫星平近点角Mk的计算
	Mk = m_M0 + n * tk;
	// 4、计算观测时刻的偏近点角Ek,用开普特方程，采用迭代算法
	double Ek1, Ek2;
	Ek1 = Mk;
	do
	{
		Ek2 = Mk + m_e * sin(Ek1);
		if (fabs(Ek2 - Ek1) <= 1e-15)  break;
		if (Ek2 == Ek1)break;
		Ek1 = Ek2;
	} while (1);
	Ek = Ek1;
	// 5、真近点角Vk的计算
	atany = sqrt(1 - m_e * m_e) * sin(Ek);
	atanz = cos(Ek) - m_e;
	if (atanz == 0)
		Vk = PI / 2;
	else if (atany == 0)
		Vk = PI;
	else
	{
		Vk = atan(fabs(atany / atanz));
		if (atany > 0 && atanz < 0)
			Vk = PI - Vk;
		else if (atany < 0 && atanz < 0)
			Vk = PI + Vk;
		else if (atany < 0 && atanz>0)
			Vk = 2 * PI - Vk;
	}
	// 6、升交距角PHIk的计算
	PHIk = Vk + m_omega;
	// 7、摄动改正项Cgam_u,Cgam_r,Cgam_i的计算
	double temp1 = cos(2 * PHIk);
	double temp2 = sin(2 * PHIk);
	Cgam_u = m_Cuc * temp1 + m_Cus * temp2;
	Cgam_r = m_Crc * temp1 + m_Crs * temp2;
	Cgam_i = m_Cic * temp1 + m_Cis * temp2;
	// 8、计算经过摄动改正的升交距角Mu_k、卫星矢径r_k和轨道倾角i_k
	Mu_k = PHIk + Cgam_u;
	r_k = m_sqrt_a * m_sqrt_a * (1 - m_e * cos(Ek)) + Cgam_r;
	i_k = m_i0 + Cgam_i + m_I * tk;
	// 9、计算卫星在轨道平面坐标系的坐标
	xk = r_k * cos(Mu_k);
	yk = r_k * sin(Mu_k);
	// 10、观测时刻升交点经度OMk的计算
	OMk = m_OM0 + (m_OM - omg_e) * tk - omg_e * m_toe;
	// 11、计算卫星在地心固定坐标系中的直角坐标
	X = xk * cos(OMk) - yk * cos(i_k) * sin(OMk);
	Y = xk * sin(OMk) + yk * cos(i_k) * cos(OMk);
	Z = yk * sin(i_k);

	//单位变为KM，以便和IGS统一
	X = X / 1000;
	Y = Y / 1000;
	Z = Z / 1000;
	//X = floor(X * 10000.000f + 0.5) / 10000.000f;

	return TRUE;
}

//打开文件
void CGPSCoordinateDlg::OnOpengbxl()
{
	CFileDialog fileDlg(true, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("导航文件 (*.??n)|*.??n|导航文件 (*.??N)|*.??N||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框  
	{
		gReadFilePathName = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名  
		GetDlgItem(IDC_EDIT1)->SetWindowText(gReadFilePathName);//将路径显示  
		CString filename = fileDlg.GetFileName();
		AfxMessageBox("导航文件打开成功!");
		iscal2 = 0;
		isopen = 1;
	}
	else
	{
		AfxMessageBox("导航文件打开失败!");
		isopen = 0;
	}
}

//计算单独卫星
void CGPSCoordinateDlg::OnBnClickedButton1()
{
	if (isopen == 1)
	{

		int state = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
		if (state == 1)
		{
			UpdateData(TRUE);
			if (Edit3.IsEmpty())
			{
				AfxMessageBox("未输入 年");
				return;
			}
			else if (Edit4.IsEmpty())
			{
				AfxMessageBox("未输入 月");
				return;
			}
			else if (Edit5.IsEmpty())
			{
				AfxMessageBox("未输入 日");
				return;
			}
			else if (Edit6.IsEmpty())
			{
				AfxMessageBox("未输入 时");
				return;
			}
			else if (Edit7.IsEmpty())
			{
				AfxMessageBox("未输入 分");
				return;
			}
			else if (Edit8.IsEmpty())
			{
				AfxMessageBox("未输入 秒");
				return;
			}
			else if (Edit9.IsEmpty())
			{
				AfxMessageBox("未输入 卫星号");
				return;
			}

			CString str;
			GetDlgItem(IDC_EDIT3)->GetWindowText(str);
			f_year = _ttoi(str);
			GetDlgItem(IDC_EDIT4)->GetWindowText(str);
			f_month = _ttoi(str);
			GetDlgItem(IDC_EDIT5)->GetWindowText(str);
			f_day = _ttoi(str);
			GetDlgItem(IDC_EDIT6)->GetWindowText(str);
			f_hour = _ttoi(str);
			GetDlgItem(IDC_EDIT7)->GetWindowText(str);
			f_minute = _ttoi(str);
			GetDlgItem(IDC_EDIT8)->GetWindowText(str);
			f_second = atof(str);
			GetDlgItem(IDC_EDIT9)->GetWindowText(str);
			f_GPSNO = _ttoi(str);


			GetGPSTime(f_year, f_month, f_day, f_hour, f_minute, f_second, gpst);

			if (f_year >= 2000)
			{
				f_year -= 2000;
			}
			if (f_year >= 1980 && f_year < 2000)
			{
				f_year -= 1980;
			}
			BOOL iscal;
			iscal = ReadOFile(gReadFilePathName, f_GPSNO, f_hour, f_minute, f_second);

			if (iscal == TRUE)
			{
				CString str;
				str.Format(_T("%d"), f_GPSNO);
				AfxMessageBox(str + "号卫星坐标计算完成！");

				str.Format(_T("%lf"), gps[f_GPSNO].X);
				GetDlgItem(IDC_EDIT8)->SetWindowText(str);

				str.Format(_T("%lf"), gps[f_GPSNO].Y);
				GetDlgItem(IDC_EDIT12)->SetWindowText(str);

				str.Format(_T("%lf"), gps[f_GPSNO].Z);
				GetDlgItem(IDC_EDIT11)->SetWindowText(str);
			}
			else
			{
				CString str;
				str.Format(_T("%d"), f_GPSNO);
				AfxMessageBox(str + "号卫星未找到！");
			}
		}
		else
		{
			AfxMessageBox("复选框未选中，不能计算单个卫星坐标！");
		}
	}
	else
	{
		AfxMessageBox("请先打开文件！");
	}
}

//计算所有卫星
void CGPSCoordinateDlg::OnBnClickedButton2()
{
	if (isopen == 1)
	{

		int state = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
		if (state == 0)
		{
			UpdateData(TRUE);
			if (Edit3.IsEmpty())
			{
				AfxMessageBox("未输入 年");
				return;
			}
			else if (Edit4.IsEmpty())
			{
				AfxMessageBox("未输入 月");
				return;
			}
			else if (Edit5.IsEmpty())
			{
				AfxMessageBox("未输入 日");
				return;
			}
			else if (Edit6.IsEmpty())
			{
				AfxMessageBox("未输入 时");
				return;
			}
			else if (Edit7.IsEmpty())
			{
				AfxMessageBox("未输入 分");
				return;
			}
			else if (Edit8.IsEmpty())
			{
				AfxMessageBox("未输入 秒");
				return;
			}

			CString str;
			GetDlgItem(IDC_EDIT3)->GetWindowText(str);
			f_year = _ttoi(str);
			GetDlgItem(IDC_EDIT4)->GetWindowText(str);
			f_month = _ttoi(str);
			GetDlgItem(IDC_EDIT5)->GetWindowText(str);
			f_day = _ttoi(str);
			GetDlgItem(IDC_EDIT6)->GetWindowText(str);
			f_hour = _ttoi(str);
			GetDlgItem(IDC_EDIT7)->GetWindowText(str);
			f_minute = _ttoi(str);
			GetDlgItem(IDC_EDIT8)->GetWindowText(str);
			f_second = atof(str);

			if (f_year < 1980)
			{
				AfxMessageBox("年份不能小于1980年");
				return;
			}
			else if (f_month == 0)
			{
				AfxMessageBox("月份不能为0");
				return;
			}
			else if (f_month > 12)
			{
				AfxMessageBox("月份不能大于12");
				return;
			}
			else if (f_day == 0)
			{
				AfxMessageBox("天不能为0");
				return;
			}
			else if (f_day > GetDaysInMonth(f_year, f_month))
			{
				CString daymax;
				daymax.Format(_T("%d"), GetDaysInMonth(f_year, f_month));
				AfxMessageBox("天数不能大于" + daymax);
				return;
			}
			else if (f_hour > 24)
			{
				AfxMessageBox("不能超过24时");
				return;
			}
			else if (f_minute > 60)
			{
				AfxMessageBox("不能超过60分");
				return;
			}
			else if (f_second > 60)
			{
				AfxMessageBox("不能超过60秒");
				return;
			}

			GetGPSTime(f_year, f_month, f_day, f_hour, f_minute, f_second, gpst);

			if (f_year >= 2000)
			{
				f_year -= 2000;
			}
			if (f_year >= 1980 && f_year < 2000)
			{
				f_year -= 1980;
			}
			BOOL iscal;
			for (int i = 1; i <= 32; i++)
			{
				f_GPSNO = i;
				iscal = ReadOFile(gReadFilePathName, f_GPSNO, f_hour, f_minute, f_second);
				if (iscal == FALSE)
				{
					CString str;
					str.Format(_T("%d"), i);
					AfxMessageBox(str + "号卫星未找到！");
				}
			}
			if (iscal == TRUE)
			{
				AfxMessageBox("所有卫星坐标计算完成，请输出文件！");
				iscal2 = 1;
			}
		}
		else
		{
			AfxMessageBox("复选框选中后不能计算所有卫星坐标！");
		}
	}
	else
	{
		AfxMessageBox("请先打开文件！");
	}

}

//打开窗口
void CGPSCoordinateDlg::OnContrast1()
{
	Contrast1  Dlg1;
	Dlg1.DoModal();
}

//保存
void CGPSCoordinateDlg::OnGpspos()
{
	if (iscal2 == 0)
	{
		AfxMessageBox("请先计算所有卫星坐标！");
	}
	else
	{

		BOOL isOpen = FALSE;        //是否打开(否则为保存)  	
		CString filter = "文本文件 (*.txt)|*.txt||";   //文件过虑的类型  
		CFileDialog openFileDlg(isOpen, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
		INT_PTR result = openFileDlg.DoModal();
		if (result == IDOK) {
			gWriteFilePathName = openFileDlg.GetPathName();
		}
		else
		{
			AfxMessageBox("保存失败!");
			return;
		}

		BOOL iswrite;
		iswrite = WritePosFile(gWriteFilePathName, gps);
		if (iswrite == TRUE)
		{
			AfxMessageBox("结果已保存!");
			GetDlgItem(IDC_EDIT2)->SetWindowText(gWriteFilePathName);//将路径显示
		}
	}
}


void CGPSCoordinateDlg::OnEnChangeEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CGPSCoordinateDlg::OnStnClickedStatic3()
{
	// TODO:  在此添加控件通知处理程序代码
}

//获取当前时间
void CGPSCoordinateDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString str;

	CTime tm = CTime::GetCurrentTime();

	str = tm.Format("%Y-%m-%d   %H:%M:%S");

	SetDlgItemText(IDC_STATIC17, str);

	CDialogEx::OnTimer(nIDEvent);
}

//打开比较窗口
void CGPSCoordinateDlg::Onigsfinal()
{
	Contrast1  Dlg1;
	Dlg1.DoModal();
}

//退出按钮
void CGPSCoordinateDlg::OnExit1()
{
	if (IDNO == ::MessageBox(this->m_hWnd, _T("退出前请保存数据，否则不可恢复，退出吗?"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO))
	{
		return;
	}
	else {

		this->SendMessage(WM_CLOSE);
	}

}


void CGPSCoordinateDlg::Onsaveonlywc()
{
	// TODO:  在此添加命令处理程序代码
}

//获取每个月有多少天
int CGPSCoordinateDlg::GetDaysInMonth(int y, int m)
{
	int d;
	int day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (2 == m)
	{
		d = (((0 == y % 4) && (0 != y % 100) || (0 == y % 400)) ? 29 : 28);
	}
	else
	{
		d = day[m - 1];

	}
	return d;
}

//弹出结果窗口，表格显示
void CGPSCoordinateDlg::OnBg1()
{
	if (iscal2 == 0)
	{
		AfxMessageBox("请先计算所有卫星坐标误差！");
	}
	else
	{
		JGBG1  Dlg2;
		Dlg2.DoModal();
	}
}

//打开“关于”窗体
void CGPSCoordinateDlg::OnAbout()
{
	ABOUT  Dlg3;
	Dlg3.DoModal();
}


