
// GeniusMonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GeniusMonitor.h"
#include "GeniusMonitorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGeniusMonitorDlg �Ի���



CGeniusMonitorDlg::CGeniusMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGeniusMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGeniusMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGeniusMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SCREENSHOT, &CGeniusMonitorDlg::OnBnClickedBtnScreenshot)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMBUTTONUP()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CGeniusMonitorDlg ��Ϣ�������

BOOL CGeniusMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	this->SetWindowPos(&wndTopMost, 0, 0, screenX, screenY, 0);
	SetWindowPos(this, 0, 0, 1, 1, NULL);

	rectScreen = CRect(0,0,screenX,screenY);

	//SetTimer(1, 1000, NULL);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGeniusMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGeniusMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	if (isClickedButton)
	{
		CImage image;
		image.Load(L"C://images//capture.bmp");
		CDC *pdc = NULL;
		pdc = GetDC();
		image.Draw(pdc->m_hDC,rectScreen);
		//image.Draw(this->m_hWnd, rectScreen);
		ReleaseDC(pdc);
	}
	if (isCapturing)
	{
		CDC *pdc = NULL;
		pdc = GetDC();
		CPen pen;
		pen.CreatePen(BS_SOLID, 2, RGB(0,0,0));
		pdc->SelectObject(pen);
		
		pdc->MoveTo(screenShotRect.left, screenShotRect.top);
		pdc->LineTo(screenShotRect.right, screenShotRect.top);
		pdc->LineTo(screenShotRect.right, screenShotRect.bottom);
		pdc->LineTo(screenShotRect.left, screenShotRect.bottom);
		pdc->LineTo(screenShotRect.left, screenShotRect.top);
		ReleaseDC(pdc);
	}
	
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGeniusMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGeniusMonitorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	screenShotRect.left = point.x;
	screenShotRect.top = point.y;

	isCapturing = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGeniusMonitorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	screenShotRect.right = point.x;
	screenShotRect.bottom = point.y;

	if (screenShotRect.left == screenShotRect.right)
	{
		AfxMessageBox(L"��ͼ�������������");
		return;
	}

	LONG tmp = 0;
	if (screenShotRect.left > screenShotRect.right)
	{
		tmp = screenShotRect.left;
		screenShotRect.left = screenShotRect.right;
		screenShotRect.right = tmp;
	}
	if (screenShotRect.top > screenShotRect.bottom)
	{
		tmp = screenShotRect.top;
		screenShotRect.top = screenShotRect.bottom;
		screenShotRect.bottom = tmp;
	}

	HBITMAP hMap = CopyScreenToBitmap(screenShotRect);
	CString imageName;
	imageName.Format(L"C://images//%d%d%d%d.bmp", screenShotRect.left, screenShotRect.right, screenShotRect.top, screenShotRect.bottom);
	//SaveBitmapToFile(hMap, imageName);
	SaveBitmapToFile(hMap, L"C://images//1.bmp");

	CString tmpCString;
	tmpCString.Format(L"�ɵ㣨%d��%d����%d��%d��", screenShotRect.left, screenShotRect.top, screenShotRect.right, screenShotRect.bottom);
	AfxMessageBox(tmpCString);

	isCapturing = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGeniusMonitorDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	screenShotRect.left = point.x;
	screenShotRect.top = point.y;

	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


void CGeniusMonitorDlg::OnNcMButtonUp(UINT nHitTest, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	screenShotRect.right = point.x;
	screenShotRect.bottom = point.y;

	if (screenShotRect.left == screenShotRect.right)
	{
		AfxMessageBox(L"��ͼ�������������");
		return;
	}

	int tmp = 0;
	if (screenShotRect.left > screenShotRect.right)
	{
		tmp = screenShotRect.left;
		screenShotRect.left = screenShotRect.right;
		screenShotRect.right = tmp;
	}
	if (screenShotRect.top > screenShotRect.bottom)
	{
		tmp = screenShotRect.top;
		screenShotRect.top = screenShotRect.bottom;
		screenShotRect.bottom = tmp;
	}

	HBITMAP hMap = CopyScreenToBitmap(screenShotRect);
	CString imageName;
	imageName.Format(L"C://images//%d%d%d%d.bmp", screenShotRect.left, screenShotRect.right, screenShotRect.top, screenShotRect.bottom);
	//SaveBitmapToFile(hMap, imageName);
	SaveBitmapToFile(hMap, L"C://images//1.bmp");

	CString tmpCString;
	tmpCString.Format(L"�ɵ㣨%d��%d����%d��%d��");
	AfxMessageBox(tmpCString);



	CDialogEx::OnNcMButtonUp(nHitTest, point);
}


//����Ļָ��������BMPͼƬ  
HBITMAP CGeniusMonitorDlg::CopyScreenToBitmap(LPRECT lpRect) //lpRect ����ѡ������  
{
	HDC hScrDC, hMemDC;
	// ��Ļ���ڴ��豸������  
	HBITMAP hBitmap, hOldBitmap;
	// λͼ���  
	int nX, nY, nX2, nY2;
	// ѡ����������  
	int nWidth, nHeight;
	// λͼ��Ⱥ͸߶�  
	int xScrn, yScrn;
	// ��Ļ�ֱ���  
	// ȷ��ѡ������Ϊ�վ���  
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������  
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������  
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������  
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// �����Ļ�ֱ���  
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���  
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// ����һ������Ļ�豸��������ݵ�λͼ  
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������  
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������  
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);
	//�õ���Ļλͼ�ľ��  
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//���  
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���  
	return hBitmap;
}


//��BMPͼƬ����ļ�
int CGeniusMonitorDlg::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName) //hBitmap Ϊ�ղŵ���Ļλͼ���  
{ //lpFileName Ϊλͼ�ļ���  
	HDC hDC;
	//�豸������  
	int iBits;
	//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���  
	WORD wBitCount;
	//λͼ��ÿ��������ռ�ֽ���  
	//�����ɫ���С�� λͼ�������ֽڴ�С �� λͼ�ļ���С �� д���ļ��ֽ���  
	DWORD dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
	BITMAP Bitmap;
	//λͼ���Խṹ  
	BITMAPFILEHEADER bmfHdr;
	//λͼ�ļ�ͷ�ṹ  
	BITMAPINFOHEADER bi;
	//λͼ��Ϣͷ�ṹ  
	LPBITMAPINFOHEADER lpbi;
	//ָ��λͼ��Ϣͷ�ṹ  
	HANDLE fh, hDib, hPal;
	HPALETTE hOldPal = NULL;
	//�����ļ��������ڴ�������ɫ����  


	//����λͼ�ļ�ÿ��������ռ�ֽ���  
	hDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) *
		GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else
		wBitCount = 32;
	//�����ɫ���С  
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount)*sizeof(RGBQUAD);


	//����λͼ��Ϣͷ�ṹ  
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
	//Ϊλͼ���ݷ����ڴ�  
	/*xxxxxxxx����λͼ��С�ֽ�һ��(����һ����������)xxxxxxxxxxxxxxxxxxxx
	//ÿ��ɨ������ռ���ֽ���Ӧ��Ϊ4���������������㷨Ϊ:
	int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
	if((Bitmap.bmWidth*wBitCount) % 32)
	biWidth++; //�����������ļ�1
	biWidth *= 4;//���������õ���Ϊÿ��ɨ���е��ֽ�����
	dwBmBitsSize = biWidth * Bitmap.bmHeight;//�õ���С
	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/


	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// �����ɫ��  
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	// ��ȡ�õ�ɫ�����µ�����ֵ  
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	//�ָ���ɫ��  
	if (hOldPal)
	{
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	//����λͼ�ļ�  
	fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;
	// ����λͼ�ļ�ͷ  
	bmfHdr.bfType = 0x4D42; // "BM"  
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	// д��λͼ�ļ�ͷ  
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// д��λͼ�ļ���������  
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize, &dwWritten, NULL);
	//���  
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

void CGeniusMonitorDlg::OnBnClickedBtnScreenshot()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_BTN_SCREENSHOT)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	Sleep(500);
	HBITMAP hMap = CopyScreenToBitmap(rectScreen);
	SaveBitmapToFile(hMap, L"C://images//capture.bmp");
	isClickedButton = true;
	OnPaint();
	this->GetDlgItem(IDC_BTN_SCREENSHOT)->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_SHOW);
}

void CGeniusMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*CString tmpCS = L"";
	tmpCS.Format(L"C://images//%d.bmp", ++noCount);
	CaptureWholeScreen(tmpCS);*/

	CDialogEx::OnTimer(nIDEvent);
}

void CGeniusMonitorDlg::CaptureWholeScreen(LPCWSTR lpFileName)
{
	HBITMAP hMap = CopyScreenToBitmap(rectScreen);
	SaveBitmapToFile(hMap, lpFileName);
}



LRESULT CGeniusMonitorDlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	

	return CDialogEx::OnNcHitTest(point);
}


void CGeniusMonitorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (isCapturing)
	{
		screenShotRect.right = point.x;
		screenShotRect.bottom = point.y;
	}
	OnPaint();

	CDialogEx::OnMouseMove(nFlags, point);
}
