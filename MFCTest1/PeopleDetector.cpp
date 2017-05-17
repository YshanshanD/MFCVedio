#include "stdafx.h"
#include "PeopleDetector.h"
#include <string.h>
#include <ctype.h>
#include "MFCTest1Dlg.h"



PeopleDetector::PeopleDetector()
{
	found_filtered_flag = true;
}


PeopleDetector::~PeopleDetector()
{
}

void PeopleDetector::process2(VideoCapture &caputure, LPVOID params)
 
{
	    CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)params;
        Mat img;  //�洢ͼ������
		//FILE* f = 0;


		if (!caputure.read(img)) return;
		Mat img_copy;
		img.copyTo(img_copy);
		
		cvtColor(img_copy, img_copy, CV_BGR2GRAY);

		/*Size win_stride=Size(), Size padding=Size(), double scale0=1.05, int group_threshold=2)
        ���ܣ��������ͼƬimg���ж�߶ȵ����˼��.
		����˵����
		img�����������ͼƬ
		found_locations����⵽��Ŀ�������б�
		hit_threshold�������ڲ�Ϊ��������Ŀ�����ֵ��Ҳ���Ǽ�⵽��������SVM���೬ƽ��ľ���
        win_stride����������ÿ���ƶ��ľ��루�����ǿ��ƶ����������� padding��ͼ������Ĵ�С
		scale0������ϵ��������������ÿ�����ӵı���
		group_threshold��У��ϵ������һ��Ŀ�걻������ڼ�����ʱ�����������.����Ϊ0�ǲ�����*/

		
		this->img = img_copy;
		if (this_back->frame_order % 10 == 0)
		{
			//found_filtered_flag = false;
			//found.clear();
			//found_filtered.clear();
			AfxBeginThread(DealPeople, this, 0, 0, 0, 0);
			
		}

		
		

		//�����ο�
		if (found_filtered_flag == true)
		{
			int i;
			BOOL flag_mid = flag;
			for (i = 0; i < found_filtered.size(); i++)
			{
				Rect r = found_filtered[i];
				// ��ΪHOG detector���ص��±�Ŀ���ľ��ο����Ӧ��С���ο�
				r.x += cvRound(r.width*0.1);
				r.width = cvRound(r.width*0.8);
				r.y += cvRound(r.height*0.07);
				r.height = cvRound(r.height*0.8);
				rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);  //img-ͼƬ��tl----the top-left corner��br----the top-left corner��Scalar()-���ο���ɫ��config6-�߿�
				if (r.y+r.height >= initBegin && flag_mid == true && this_back->frame_order%30 == 0)
				{
					//flag_mid = false;
					//AfxBeginThread(NotifyPeople, this, 0, 0, 0, 0);
					//MessageBeep(MB_OK);
					//Beep(5000, 500);
					MessageBeep(MB_NOFOCUS);
					//Sleep(1000);
					
				}
			}
		}
		resize(img, img, Size(this_back->picture_y, this_back->picture_x));
	    if(this_back->peopleDetector.flag==true)
		line(img,Point(this_back->peopleDetector.initBegin, this_back->peopleDetector.initEnd),Point(this_back->peopleDetector.finaBegin, this_back->peopleDetector.finaEnd),Scalar(0,0,255),2);
		//line(img, Point(280, 180), Point(280, 200), Scalar(99, 100, 33),2);
		imshow("vehicle", img);
			  
}

void PeopleDetector::onMouseAction(int event, int x, int y, int flags, void * ustc)
{
	    PeopleDetector *this_flag = (PeopleDetector *)ustc;
		int base_i;
		if (event == CV_EVENT_MOUSEMOVE)
		{
			cout << "��������ƶ��¼�" << endl;
		}
		if (event == CV_EVENT_LBUTTONDOWN)
		{
			this_flag->initBegin = x;
			this_flag->initEnd = y;
			this_flag->flag = false;
		}
		if (event == CV_EVENT_LBUTTONUP)
		{
			this_flag->finaBegin = x;
			this_flag->finaEnd = y;
			this_flag->flag = true;
			
		}
	}

UINT PeopleDetector::DealPeople(LPVOID pParam)
{
	PeopleDetector* p = (PeopleDetector*)pParam;
	HOGDescriptor hog;  //HOG����������
	vector<Rect> found, found_filtered;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());  //�õ�SVM�������----���ڶ�hog�������з����svmģ�͵�ϵ����ֵ
	hog.detectMultiScale(p->img, found, 0, Size(8, 8), Size(0, 0), 1.35, 2);
	
	size_t i, j;
	//�ҳ�û��Ƕ�׵ľ��ο�r�������Ƕ�׵Ļ���������ľ��ο�
	for (i = 0; i < found.size(); i++)
	{
		Rect r = found[i];
		for (j = 0; j < found.size(); j++)
			if (j != i && (r & found[j]) == r)
				break;
		if (j == found.size())
			found_filtered.push_back(r);
	}
	p->found_filtered = found_filtered;
	p->found_filtered_flag = true;
	return 0;
}

UINT PeopleDetector::NotifyPeople(LPVOID pParam)
{
	PeopleDetector* this_back = (PeopleDetector*)pParam;
	int i = 0;
	
	MessageBeep(MB_OK);
	//Sleep(250);
	
	//this_back->flag = true;
	return 0;
}




