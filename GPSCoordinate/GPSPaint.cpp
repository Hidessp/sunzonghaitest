// GPSPaint.cpp : ʵ���ļ�
//

#include "framework.h"
#include "GPSCoordinate.h"
#include "GPSPaint.h"
#include "afxdialogex.h"
#include "GPS.h"

extern GPS gps[50];


//��ʼ��    


// GPSPaint �Ի���

IMPLEMENT_DYNAMIC(GPSPaint, CDialogEx)

GPSPaint::GPSPaint(CWnd* pParent /*=NULL*/)
	: CDialogEx(GPSPaint::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// ������m_nzValues��Ԫ�ض���ʼ��Ϊ0   
	memset(m_nzValues, 0, sizeof(int) * POINT_COUNT);

	//��ʼ������
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


// GPSPaint ��Ϣ�������


BOOL GPSPaint::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

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

	// ��ʱ��Ϊ���������������������   
	srand((unsigned)time(NULL));

	// ������ʱ����IDΪ1����ʱʱ��Ϊ200ms   
	SetTimer(1, 200, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//���Ʋ���ͼ
void GPSPaint::DrawWave(CDC* pDC, CRect& rectPicture)
{
	float fDeltaX;     // x������������ͼ����������   
	float fDeltaY;     // y��ÿ���߼���λ��Ӧ������ֵ   
	int nX;      // ������ʱ���ڴ洢��ͼ��ĺ�����   
	int nY;      // ������ʱ���ڴ洢��ͼ���������   
	CPen newPen;       // ���ڴ����»���   
	CPen* pOldPen;     // ���ڴ�žɻ���   
	CBrush newBrush;   // ���ڴ����»�ˢ   
	CBrush* pOldBrush; // ���ڴ�žɻ�ˢ   

	// ����fDeltaX��fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	pDC->Rectangle(rectPicture);
	// �ָ��ɻ�ˢ   
	pDC->SelectObject(pOldBrush);
	// ɾ���»�ˢ   
	newBrush.DeleteObject();

	// ����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ   
	newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	// ����ǰ���ƶ�����ͼ�ؼ����ڵ����½ǣ��Դ�Ϊ���ε���ʼ��   
	pDC->MoveTo(rectPicture.left, rectPicture.bottom);
	// ����m_nzValues������ÿ�����Ӧ������λ�ã����������ӣ������γ�����   
	for (int i = 0; i < POINT_COUNT; i++)
	{
		nX = rectPicture.left + (int)(i * fDeltaX);
		nY = rectPicture.bottom - (int)(m_nzValues[i] * fDeltaY);
		pDC->LineTo(nX, nY);
	}

	// �ָ��ɻ���   
	pDC->SelectObject(pOldPen);
	// ɾ���»���   
	newPen.DeleteObject();
}

//����GPS����ͼ
void GPSPaint::DrawGPS(CDC* pDC, CRect& rectPicture)
{
	float fDeltaX;     // x������������ͼ����������   
	float fDeltaY;     // y��ÿ���߼���λ��Ӧ������ֵ   
	int nX;      // ������ʱ���ڴ洢��ͼ��ĺ�����   
	int nY;      // ������ʱ���ڴ洢��ͼ���������   
	CPen newPen;       // ���ڴ����»���   
	CPen* pOldPen;     // ���ڴ�žɻ���   
	CBrush newBrush;   // ���ڴ����»�ˢ   
	CBrush* pOldBrush; // ���ڴ�žɻ�ˢ   

	// ����fDeltaX��fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	pDC->Rectangle(rectPicture);
	// ɾ���»�ˢ   
	newBrush.DeleteObject();
	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(255, 255, 255));
	//����ʵ��Բ
	pDC->BeginPath();
	pDC->Ellipse(5000, 10000, 100, 100);
	pDC->EndPath();
	pDC->SelectObject(&newBrush);
	pDC->FillPath();
	// �ָ��ɻ�ˢ   
	pDC->SelectObject(pOldBrush);
	// ɾ���»�ˢ   
	newBrush.DeleteObject();

	// ����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ   
	newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen   
	pOldPen = pDC->SelectObject(&newPen);
	// �ָ��ɻ���   
	pDC->SelectObject(pOldPen);
	// ɾ���»���   
	newPen.DeleteObject();
}

//˫�����ͼ   
void GPSPaint::Invalidate()
{

	HDC hdc = ::GetDC(m_hWnd);
	CDC dc;
	dc.Attach(hdc);
	CDC memDC;
	CBitmap MemBitmap;
	// �豸�������ʼ��   
	memDC.CreateCompatibleDC(NULL);
	// ��������Ļ��ʾ���ݵ��ڴ���ʾ�豸   
	MemBitmap.CreateCompatibleBitmap(&dc, m_Rect.Width(), m_Rect.Height());
	// ѡȡ�հ�λͼ   
	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, m_Rect.Width(), m_Rect.Height(), RGB(255, 255, 255));
	//��ͼ   
	Draw(&memDC);
	//�������ؼ�DC   
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rectPicture;

	m_picDraw.GetClientRect(&rectPicture);

	// ���Ʋ���ͼ   
	DrawWave(m_picDraw.GetDC(), rectPicture);

	CDialogEx::OnTimer(nIDEvent);
}


void GPSPaint::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	// �رն�ʱ��   
	KillTimer(1);
}


void GPSPaint::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void GPSPaint::OnPaint()
{

	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CDialogEx::OnPaint();

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HCURSOR GPSPaint::OnQueryDragIcon()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return static_cast<HCURSOR>(m_hIcon);
	//return CDialogEx::OnQueryDragIcon();
}



void GPSPaint::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void GPSPaint::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void GPSPaint::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nFlags & MK_LBUTTON)
	{
		REAL deltaX = point.x - m_mouseDown.X; //x�᷽��ƫ��   
		REAL deltaY = point.y - m_mouseDown.Y; //y�᷽��ƫ��   

		m_imgX = (m_PtStart.X + (deltaX / m_zoom)); //��ԭʼͼ����X����ƫ�ƣ�������������ԭʼͼƬ�е�λ�ƣ�ԭ���������Ѿ�˵����ȫ�ֵķ���任��Ӱ��ʵ�ʵ�λ��  
		m_imgY = (m_PtStart.Y + (deltaY / m_zoom)); //��ԭʼͼ����Y����ƫ��   
		Invalidate(); //�ػ�   
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL GPSPaint::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	REAL oldzoom = m_zoom; //���浱ǰ������ϵ�������ڼ��㵱ǰ����ʱ������   
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

	GetWindowRect(rect); //ע������������Ǵ��������������Ļ�ģ���Ϊcpoint pt<span style="font-family: Arial, Helvetica, sans-serif;">��������������Ļ��</span>  

	ppt.x -= rect.left; //����õ��ڶԻ����е�λ��   
	ppt.y -= rect.top;

	int x = ppt.x - m_Rect.left;
	int y = ppt.y - m_Rect.top;

	REAL oldimagex = (x / oldzoom); //����ǰ�����ԭͼ�е�λ��   
	REAL oldimagey = (y / oldzoom);

	REAL newimagex = (x / m_zoom);//<span style="font-family: Arial, Helvetica, sans-serif;">���ź������ԭͼ�е�λ��</span>  
	REAL newimagey = (y / m_zoom);

	m_imgX = newimagex - oldimagex + m_imgX; //����ԭͼӦ�õ�ƫ��   
	m_imgY = newimagey - oldimagey + m_imgY;

	Invalidate(); //��ͼ   

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void GPSPaint::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_mousepressed = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}
