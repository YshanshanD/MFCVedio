
// MFCTest1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Blob.h"
#include "afxmenubutton.h"
#include "VehicleDetector.h"
#include "PeopleDetector.h"


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
public:
	int picture_x;
	int picture_y;
public:
	CEdit show_text;
	CEdit show_text2;
	vector<Blob> blobs; // �����ſ�
	vector<Blob> pre_blobs; // ǰһ֡���ſ�
	vector<Blob> cur_blobs; // ��ǰ֡���ſ�
	int count=0; // ��������
	int count2=0;
	CSplitButton choose;
	afx_msg void OnUpdateCaption1(CCmdUI *pCmdUI);

	int frame_order;

	static const int VERICHL_COUNT = 1;//����1 �������
	static const int PEOPLE_DETECT = 2;//����2 ����Υ����
	static const int NO_FUNCTION = -1;//δѡ����

	int current_func = NO_FUNCTION;//����ǰ����ѡ��
	afx_msg void OnUpdateCaption2(CCmdUI *pCmdUI);
	VehicleDetector vehicleDetector;

	PeopleDetector peopleDetector;
};
