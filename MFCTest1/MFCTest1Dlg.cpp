
// MFCTest1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest1.h"
#include "MFCTest1Dlg.h"
#include "afxdialogex.h"
#include "MyTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCTest1Dlg �Ի���



CMFCTest1Dlg::CMFCTest1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHARE, picture_share);
	DDX_Control(pDX, PAUSE, stopbtn);
	DDX_Control(pDX, IDC_EDIT1, show_text);
}

BEGIN_MESSAGE_MAP(CMFCTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(PAUSE, &CMFCTest1Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_BTN_END, &CMFCTest1Dlg::OnBnClickedBtnEnd)
	ON_BN_CLICKED(BTNSTART, &CMFCTest1Dlg::OnBnClickedBtnstart)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCTest1Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMFCTest1Dlg ��Ϣ��������

BOOL CMFCTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

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

	// TODO: �ڴ����Ӷ���ĳ�ʼ������

	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_SHARE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_SHARE);//IDC_PIC_2DΪ�ؼ�ID
	pWnd->GetClientRect(&rc);//rcΪ�ؼ��Ĵ�С��
	picture_x = rc.Height();
	picture_y = rc.Width();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCTest1Dlg::OnPaint()
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
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CMFCTest1Dlg::PlayVideo(LPVOID pParam)
{
	VideoCapture capture("D:\\video_test_1.mp4");
	//VideoCapture capture(0);
	Mat pictureBackground;
	int frame_order = 0;
	//VideoCapture capture(0);
	CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)pParam;

	
	while (1)
	{
		MSG my_msg;
		if(PeekMessage(&my_msg, 0, 0, 0, PM_REMOVE)) 
		{
			if (my_msg.message == WM_QUIT)
			{
				capture.release();
				return 0;
			}
		}
		else 
		{
			Mat frame;
			if (CMFCTest1Dlg::playFlag == 1)
			{
				capture.set(CV_CAP_PROP_POS_FRAMES, 0);
				CMFCTest1Dlg::playFlag = 0;
				frame_order = 0;
			}
			if (CMFCTest1Dlg::playFlag == 0)
			{
				
				
				if (frame_order % 10 == 0)
				{
					pictureBackground = MyTools::getPictureBackground(capture, frame_order);
					medianBlur(pictureBackground, pictureBackground, 3);
					//
					Mat mid_three;
					resize(pictureBackground, mid_three, Size(this_back->picture_y, this_back->picture_x));
					imshow("����ͼ", mid_three);
					imwrite("lala.jpg",pictureBackground);
					
				}
				//cvtColor(pictureBackground, mid, COLOR_BGR2GRAY);
				//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
				//Mat dstImage;
				//erode(frame, dstImage, element);
				//blur(mid, mid, Size(7, 7));
				//Canny(mid, mid, 0, 30, 3);
				
				if (!capture.read(frame)) break;
				Mat mid;
				cvtColor(frame, frame, COLOR_BGR2GRAY);
				medianBlur(frame, frame, 3);

				Mat mid_one,mid_two;
				resize(frame, mid_one, Size(this_back->picture_y, this_back->picture_x));
				imshow("frame_median.jpg", mid_one);
				subtract(frame, pictureBackground, frame);
				resize(frame, mid_two, Size(this_back->picture_y, this_back->picture_x));
				imshow("���ͼ.jpg", mid_two);

				//���ô�С����������
				Mat des = Mat::zeros(this_back->picture_x, this_back->picture_y, CV_8UC3);
				resize(frame, des, des.size());
				
				
				Mat dst;
				double thres_value;
				thres_value = threshold(des, dst, 0, 255, CV_THRESH_OTSU);
				
				//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
				//erode(dst, dst, element);

				CString mid_value;
				mid_value.Format(L"%lf", thres_value);
				//this_back->show_text.SetWindowTextW(mid_value);
				this_back->SetDlgItemText(IDC_EDIT1, mid_value);
				

				imshow("view", dst);
				
				frame_order++;
			}
			if (CMFCTest1Dlg::playFlag == 3)
			{
				break;
			}
			waitKey(30);
		}
	}
	capture.release();
	return 0;
}



void CMFCTest1Dlg::OnBnClickedPause()
{
	CString buttonText;
	stopbtn.GetWindowText(buttonText);

	if (CMFCTest1Dlg::playFlag != 0)
	{
		CMFCTest1Dlg::playFlag = 0;
		stopbtn.SetWindowTextW(_T("����"));

	}
	else
	{
		CMFCTest1Dlg::playFlag = 2;
		stopbtn.SetWindowText(_T("��ͣ"));
	}
}


void CMFCTest1Dlg::OnBnClickedBtnEnd()
{
	CMFCTest1Dlg::playFlag = 3;
	::PostThreadMessage(playThread->m_nThreadID, WM_QUIT, 0, 0);
}


void CMFCTest1Dlg::OnBnClickedBtnstart()
{
	//LPVOID param;
	int mid = CMFCTest1Dlg::playFlag;
	CMFCTest1Dlg::playFlag = 1;
	if (mid != 2 || playThread == NULL)
	{
		//LPVOID param;
		playThread = AfxBeginThread(PlayVideo,this, 0, 0, 0, 0);
	}
}

int CMFCTest1Dlg::playFlag = 2;

void CMFCTest1Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
}