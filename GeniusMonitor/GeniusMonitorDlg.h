
// GeniusMonitorDlg.h : ͷ�ļ�
//

#pragma once


// CGeniusMonitorDlg �Ի���
class CGeniusMonitorDlg : public CDialogEx
{
	// ����
public:
	CGeniusMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_GENIUSMONITOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	void CaptureWholeScreen(LPCWSTR lpFileName);//��ȡ������Ļ������
	bool isClickedButton = false;//������ť������
	bool isCapturing = false;//�����ֶ�ѡȡ��������
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};