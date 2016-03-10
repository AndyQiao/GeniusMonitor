
// GeniusMonitorDlg.h : 头文件
//

#pragma once


// CGeniusMonitorDlg 对话框
class CGeniusMonitorDlg : public CDialogEx
{
	// 构造
public:
	CGeniusMonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_GENIUSMONITOR_DIALOG };

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
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);
	int SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName);
	afx_msg void OnBnClickedBtnScreenshot();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcMButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	int noCount = 1;
	CRect rectScreen;
	CRect screenShotRect;
	void CaptureWholeScreen(LPCWSTR lpFileName);//截取整个屏幕并保存
	bool isClickedButton = false;//截屏按钮被按下
	bool isCapturing = false;//正在手动选取窗口区域
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};