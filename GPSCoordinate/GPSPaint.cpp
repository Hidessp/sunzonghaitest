// GPSPaint.cpp : 实现文件
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "GPSPaint.h"
#include "afxdialogex.h"
#include "GPS.h"

extern GPS gps[50];


//初始化    


// GPSPaint 对话框

IMPLEMENT_DYNAMIC(GPSPaint, CDialogEx)

GPSPaint::GPSPaint(CWnd* pParent /*=NULL*/)
	: CDialogEx(GPSPaint::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 将数组m_nzValues的元素都初始化为0   
	memset(m_nzValues, 0, sizeof(int) * POINT_COUNT);

	//初始化变量
	m_zoom = 1.0f;
	m_imgX = 0.0f;
	m_imgY = 0.0f;
	m_PtStart.X = 0.0f;
	m_PtStart.Y = 0.0f;

	m_mousepressed = false;
}

GPSPaint::~GPSPaint()
{
}

void GPSPaint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAVE_DRAW, m_picDraw);

}


BEGIN_MESSAGE_MAP(GPSPaint, CDialogEx)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// GPSPaint 消息处理程序


BOOL GPSPaint::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	GetClientRect(m_Rect);
	// IDM_ABOUTBOX must be in the system command range.   
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

	// Set the icon for this dialog.  The framework does this automatically   
	//  when the application's main window is not a dialog   
	SetIcon(m_hIcon, TRUE);         // Set big icon   
	SetIcon(m_hIcon, FALSE);        // Set small icon   

	// TODO: Add extra initialization here   

	// 以时间为种子来构造随机数生成器   
	srand((unsigned)time(NULL));

	// 启动定时器，ID为1，定时时间为200ms   
	SetTimer(1, 200, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//绘制波形图
void GPSPaint::DrawWave(CDC* pDC, CRect& rectPicture)
{
	float fDeltaX;     // x轴相邻两个绘图点的坐标距离   
	float fDeltaY;     // y轴每个逻辑单位对应的坐标值   
	int nX;      // 在连线时用于存储绘图点的横坐标   
	int nY;      // 在连线时用于存储绘图点的纵坐标   
	CPen newPen;       // 用于创建新画笔   
	CPen* pOldPen;     // 用于存放旧画笔   
	CBrush newBrush;   // 用于创建新画刷   
	CBrush* pOldBrush; // 用于存放旧画刷   

	// 计算fDeltaX和fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	pDC->Rectangle(rectPicture);
	// 恢复旧画刷   
	pDC->SelectObject(pOldBrush);
	// 删除新画刷   
	newBrush.DeleteObject();

	// 创建实心画笔，粗度为1，颜色为绿色   
	newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// 选择新画笔，并将旧画笔的指针保存到pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	// 将当前点移动到绘图控件窗口的左下角，以此为波形的起始点   
	pDC->MoveTo(rectPicture.left, rectPicture.bottom);
	// 计算m_nzValues数组中每个点对应的坐标位置，并依次连接，最终形成曲线   
	for (int i = 0; i < POINT_COUNT; i++)
	{
		nX = rectPicture.left + (int)(i * fDeltaX);
		nY = rectPicture.bottom - (int)(m_nzValues[i] * fDeltaY);
		pDC->LineTo(nX, nY);
	}

	// 恢复旧画笔   
	pDC->SelectObject(pOldPen);
	// 删除新画笔   
	newPen.DeleteObject();
}

//绘制GPS卫星图
void GPSPaint::DrawGPS(CDC* pDC, CRect& rectPicture)
{
	float fDeltaX;     // x轴相邻两个绘图点的坐标距离   
	float fDeltaY;     // y轴每个逻辑单位对应的坐标值   
	int nX;      // 在连线时用于存储绘图点的横坐标   
	int nY;      // 在连线时用于存储绘图点的纵坐标   
	CPen newPen;       // 用于创建新画笔   
	CPen* pOldPen;     // 用于存放旧画笔   
	CBrush newBrush;   // 用于创建新画刷   
	CBrush* pOldBrush; // 用于存放旧画刷   

	// 计算fDeltaX和fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	pDC->Rectangle(rectPicture);
	// 删除新画刷   
	newBrush.DeleteObject();
	// 创建白色新画刷   
	newBrush.CreateSolidBrush(RGB(255, 255, 255));
	//创建实心圆
	pDC->BeginPath();
	pDC->Ellipse(5000, 10000, 100, 100);
	pDC->EndPath();
	pDC->SelectObject(&newBrush);
	pDC->FillPath();
	// 恢复旧画刷   
	pDC->SelectObject(pOldBrush);
	// 删除新画刷   
	newBrush.DeleteObject();

	// 创建实心画笔，粗度为1，颜色为绿色   
	newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// 选择新画笔，并将旧画笔的指针保存到pOldPen   
	pOldPen = pDC->SelectObject(&newPen);
	// 恢复旧画笔   
	pDC->SelectObject(pOldPen);
	// 删除新画笔   
	newPen.DeleteObject();
}

//双缓冲绘图   
void GPSPaint::Invalidate()
{

	HDC hdc = ::GetDC(m_hWnd);
	CDC dc;
	dc.Attach(hdc);
	CDC memDC;
	CBitmap MemBitmap;
	// 设备描述表初始化   
	memDC.CreateCompatibleDC(NULL);
	// 建立与屏幕显示兼容的内存显示设备   
	MemBitmap.CreateCompatibleBitmap(&dc, m_Rect.Width(), m_Rect.Height());
	// 选取空白位图   
	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, m_Rect.Width(), m_Rect.Height(), RGB(255, 255, 255));
	//画图   
	Draw(&memDC);
	//拷贝到控件DC   
	dc.BitBlt(0, 0, m_Rect.Width(), m_Rect.Height(), &memDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	memDC.DeleteDC();
	dc.Detach();
	::ReleaseDC(m_hWnd, hdc);
}

void GPSPaint::Draw(CDC* pDC)
{
}

void GPSPaint::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rectPicture;

	m_picDraw.GetClientRect(&rectPicture);

	// 绘制波形图   
	DrawWave(m_picDraw.GetDC(), rectPicture);

	CDialogEx::OnTimer(nIDEvent);
}


void GPSPaint::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	// 关闭定时器   
	KillTimer(1);
}


void GPSPaint::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void GPSPaint::OnPaint()
{

	CPaintDC dc(this); // 用于绘制的设备上下文

	CDialogEx::OnPaint();

	// 不为绘图消息调用 CDialogEx::OnPaint()
}


HCURSOR GPSPaint::OnQueryDragIcon()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return static_cast<HCURSOR>(m_hIcon);
	//return CDialogEx::OnQueryDragIcon();
}



void GPSPaint::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void GPSPaint::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void GPSPaint::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nFlags & MK_LBUTTON)
	{
		REAL deltaX = point.x - m_mouseDown.X; //x轴方向偏移   
		REAL deltaY = point.y - m_mouseDown.Y; //y轴方向偏移   

		m_imgX = (m_PtStart.X + (deltaX / m_zoom)); //在原始图像中X坐标偏移，这里计算的是在原始图片中的位移，原因在上面已经说明，全局的仿射变换会影响实际的位移  
		m_imgY = (m_PtStart.Y + (deltaY / m_zoom)); //在原始图像中Y坐标偏移   
		Invalidate(); //重绘   
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL GPSPaint::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	REAL oldzoom = m_zoom; //保存当前的缩放系数，用于计算当前滚动时的坐标   
	CPoint ppt = pt;
	CRect rect;
	if (zDelta == 120)
	{
		m_zoom += 0.4f;
	}
	if (zDelta == -120)
	{
		m_zoom = m_zoom - 0.4f;
	}

	GetWindowRect(rect); //注意这里的区域是窗口相对于整个屏幕的，因为cpoint pt<span style="font-family: Arial, Helvetica, sans-serif;">这个点是相对于屏幕的</span>  

	ppt.x -= rect.left; //计算该点在对话框中的位置   
	ppt.y -= rect.top;

	int x = ppt.x - m_Rect.left;
	int y = ppt.y - m_Rect.top;

	REAL oldimagex = (x / oldzoom); //缩放前鼠标在原图中的位置   
	REAL oldimagey = (y / oldzoom);

	REAL newimagex = (x / m_zoom);//<span style="font-family: Arial, Helvetica, sans-serif;">缩放后鼠标在原图中的位置</span>  
	REAL newimagey = (y / m_zoom);

	m_imgX = newimagex - oldimagex + m_imgX; //计算原图应该的偏移   
	m_imgY = newimagey - oldimagey + m_imgY;

	Invalidate(); //绘图   

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void GPSPaint::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nFlags & MK_LBUTTON)
	{
		if (!m_mousepressed)
		{
			m_mousepressed = true;
			m_mouseDown.X = point.x;
			m_mouseDown.Y = point.y;
			m_PtStart.X = m_imgX;
			m_PtStart.Y = m_imgY;
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void GPSPaint::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_mousepressed = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}
