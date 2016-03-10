
// GeniusMonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GeniusMonitor.h"
#include "GeniusMonitorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CGeniusMonitorDlg 对话框



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


// CGeniusMonitorDlg 消息处理程序

BOOL CGeniusMonitorDlg::OnInitDialog()
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
	
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	this->SetWindowPos(&wndTopMost, 0, 0, screenX, screenY, 0);
	SetWindowPos(this, 0, 0, 1, 1, NULL);

	rectScreen = CRect(0,0,screenX,screenY);

	//SetTimer(1, 1000, NULL);
	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGeniusMonitorDlg::OnPaint()
{
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGeniusMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGeniusMonitorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	screenShotRect.left = point.x;
	screenShotRect.top = point.y;

	isCapturing = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGeniusMonitorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	screenShotRect.right = point.x;
	screenShotRect.bottom = point.y;

	if (screenShotRect.left == screenShotRect.right)
	{
		AfxMessageBox(L"截图区域出错！请重试");
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
	tmpCString.Format(L"采点（%d，%d）（%d，%d）", screenShotRect.left, screenShotRect.top, screenShotRect.right, screenShotRect.bottom);
	AfxMessageBox(tmpCString);

	isCapturing = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGeniusMonitorDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	screenShotRect.left = point.x;
	screenShotRect.top = point.y;

	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


void CGeniusMonitorDlg::OnNcMButtonUp(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	screenShotRect.right = point.x;
	screenShotRect.bottom = point.y;

	if (screenShotRect.left == screenShotRect.right)
	{
		AfxMessageBox(L"截图区域出错！请重试");
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
	tmpCString.Format(L"采点（%d，%d）（%d，%d）");
	AfxMessageBox(tmpCString);



	CDialogEx::OnNcMButtonUp(nHitTest, point);
}


//将屏幕指定区域存成BMP图片  
HBITMAP CGeniusMonitorDlg::CopyScreenToBitmap(LPRECT lpRect) //lpRect 代表选定区域  
{
	HDC hScrDC, hMemDC;
	// 屏幕和内存设备描述表  
	HBITMAP hBitmap, hOldBitmap;
	// 位图句柄  
	int nX, nY, nX2, nY2;
	// 选定区域坐标  
	int nWidth, nHeight;
	// 位图宽度和高度  
	int xScrn, yScrn;
	// 屏幕分辨率  
	// 确保选定区域不为空矩形  
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表  
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表  
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标  
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// 获得屏幕分辨率  
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的  
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
	// 创建一个与屏幕设备描述表兼容的位图  
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// 把新位图选到内存设备描述表中  
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中  
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);
	//得到屏幕位图的句柄  
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//清除  
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// 返回位图句柄  
	return hBitmap;
}


//将BMP图片存成文件
int CGeniusMonitorDlg::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName) //hBitmap 为刚才的屏幕位图句柄  
{ //lpFileName 为位图文件名  
	HDC hDC;
	//设备描述表  
	int iBits;
	//当前显示分辨率下每个像素所占字节数  
	WORD wBitCount;
	//位图中每个像素所占字节数  
	//定义调色板大小， 位图中像素字节大小 ， 位图文件大小 ， 写入文件字节数  
	DWORD dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
	BITMAP Bitmap;
	//位图属性结构  
	BITMAPFILEHEADER bmfHdr;
	//位图文件头结构  
	BITMAPINFOHEADER bi;
	//位图信息头结构  
	LPBITMAPINFOHEADER lpbi;
	//指向位图信息头结构  
	HANDLE fh, hDib, hPal;
	HPALETTE hOldPal = NULL;
	//定义文件，分配内存句柄，调色板句柄  


	//计算位图文件每个像素所占字节数  
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
	//计算调色板大小  
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount)*sizeof(RGBQUAD);


	//设置位图信息头结构  
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
	//为位图内容分配内存  
	/*xxxxxxxx计算位图大小分解一下(解释一下上面的语句)xxxxxxxxxxxxxxxxxxxx
	//每个扫描行所占的字节数应该为4的整数倍，具体算法为:
	int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
	if((Bitmap.bmWidth*wBitCount) % 32)
	biWidth++; //不是整数倍的加1
	biWidth *= 4;//到这里，计算得到的为每个扫描行的字节数。
	dwBmBitsSize = biWidth * Bitmap.bmHeight;//得到大小
	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/


	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// 处理调色板  
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	// 获取该调色板下新的像素值  
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	//恢复调色板  
	if (hOldPal)
	{
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	//创建位图文件  
	fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;
	// 设置位图文件头  
	bmfHdr.bfType = 0x4D42; // "BM"  
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	// 写入位图文件头  
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// 写入位图文件其余内容  
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize, &dwWritten, NULL);
	//清除  
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

void CGeniusMonitorDlg::OnBnClickedBtnScreenshot()
{
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	

	return CDialogEx::OnNcHitTest(point);
}


void CGeniusMonitorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (isCapturing)
	{
		screenShotRect.right = point.x;
		screenShotRect.bottom = point.y;
	}
	OnPaint();

	CDialogEx::OnMouseMove(nFlags, point);
}
