
// MFCTest1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFCTest1Dlg �Ի���
class CMFCTest1Dlg : public CDialogEx
{
// ����
public:
	CMFCTest1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST1_DIALOG };
#endif

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
	CStatic picture_share;
	
public:
	static UINT PlayVideo(LPVOID pParam);
	CWinThread* playThread;
	CButton stopbtn;
	static int playFlag;
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedBtnEnd();
	afx_msg void OnBnClickedBtnstart();
private:
	int picture_x;
	int picture_y;
public:
	afx_msg void OnEnChangeEdit1();
	CEdit show_text;
};
