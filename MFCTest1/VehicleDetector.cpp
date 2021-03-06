#include "stdafx.h"
#include "VehicleDetector.h"
#include "MFCTest1Dlg.h"
#include "MyTools.h"
#include "resource.h"



VehicleDetector::VehicleDetector()
{
	for (int i = 0; i < 11; i++)
	{
		lines[i] = 0;
	}
}


VehicleDetector::~VehicleDetector()
{
}

void VehicleDetector::onMouseAction(int event, int x, int y, int flags, void * ustc)
{
	VehicleDetector *this_flag = (VehicleDetector *)ustc;
	int base_i;
	if (this_flag->lines[5] == false) base_i = 1;
	else if (this_flag->lines[10] == false) base_i = 6;
	else return;
	if (event == CV_EVENT_MOUSEMOVE) 
	{
		cout << "��������ƶ��¼�" << endl;
	}
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		this_flag->initBegin= x;
		this_flag->initEnd = y;
		this_flag->flag = false;
		this_flag->lines[base_i + 0] = x;
		this_flag->lines[base_i + 1] = y;
		this_flag->lines[base_i + 4] = 0;
	}
	if(event==CV_EVENT_LBUTTONUP)
	{
		this_flag->finaBegin = x;
		this_flag->finaEnd = y;
		//line(this_flag->frame_mid, Point(this_flag->initBegin, this_flag->initEnd), Point(this_flag->finaBegin, this_flag->finaEnd), Scalar(0, 0, 255), 2);
		this_flag->flag = true;
		this_flag->lines[base_i + 2] = x;
		this_flag->lines[base_i + 3] = y;
		this_flag->lines[base_i + 4] = 1;
	}
}
void VehicleDetector::process(VideoCapture &capture, LPVOID params)
{
	//int flag = false;
	int frame_order = capture.get(CV_CAP_PROP_POS_FRAMES);
	Mat frame;
	CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)params;
	if (frame_order % 1000 == 0)
	{
		pictureBackground = MyTools::getPictureBackground(capture, frame_order);
		//imshow("����ͼ", pictureBackground);
		medianBlur(pictureBackground, pictureBackground, 3);
		Mat mid_three;
	}

	if (!capture.read(frame)) return;
	Mat mid;
	frame.copyTo(frame_mid);
	
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	//imshow("�ҶȻ�ͼ",frame);
	medianBlur(frame,frame,3);
	//imshow("�˲�ͼ",frame);
	
	(frame, frame, 3);

	Mat mid_one, mid_two;
	resize(frame, mid_one, Size(this_back->picture_y, this_back->picture_x));
	//imshow("frame_median.jpg", mid_one);
	absdiff(frame, pictureBackground, frame);
	resize(frame, mid_two, Size(this_back->picture_y, this_back->picture_x));
	//imshow("���ͼ", mid_two);
	//���ô�С����������
	Mat des = Mat::zeros(this_back->picture_x, this_back->picture_y, CV_8UC3);
	resize(frame, des, des.size());   


	Mat dst;
	double thres_value;
	thres_value = threshold(des, dst, 0, 255, CV_THRESH_OTSU);
	//imwrite("D:\\dst.jpg", dst);
	//imshow("��ֵ��ͼ", dst);

	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat element_dilate = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(dst, dst, element);
	//imshow("��ʴͼ", dst);
	dilate(dst, dst, element_dilate);
	//imshow("����ͼ", dst);
    resize(frame_mid, frame_mid, Size(this_back->picture_y, this_back->picture_x));


	vector<vector<Point>> countours, deal_contours;
	vector<Point> approx;
	findContours(dst, countours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < countours.size(); i++)
	{
		//approxPolyDP(Mat(countours[i]), approx, arcLength(Mat(countours[i]), true)*0.02, true);
		approxPolyDP(Mat(countours[i]), approx, 0.5, true);

		if (approx.size() >= 3 && contourArea(Mat(countours[i])) > 50 && contourArea(Mat(countours[i])) < 2000)
		{
			deal_contours.push_back(countours[i]);
			Rect rect = boundingRect(countours[i]);
			Blob mid;//�ſ�
			mid.rect = rect;
			mid.id = this_back->blobs.size() + 1;
			Moments m;
			m = moments(approx);
			mid.xx = m.m10 / m.m00;
			mid.yy = m.m01 / m.m00;
			this_back->blobs.push_back(mid);
			circle(frame_mid, Point(mid.xx, mid.yy), 5, Scalar(0.234, 243));
			int begin =(lines[1] + lines[3]) / 2 ;
			int end = (lines[6] + lines[8]) / 2 ;
			if (mid.yy<=lines[4]&& mid.yy>=lines[2] && mid.xx >=(begin-3)&& mid.xx<=begin+3) this_back->count++;
			if (mid.yy <= lines[9] && mid.yy >= lines[7] && mid.xx >=end-5 && mid.xx<=end+5) this_back->count2++;
			
		}
	}
	for (size_t i = 0; i < deal_contours.size(); i++)
	{
		//const Point* p = &deal_contours[i][0];
		Rect rect = boundingRect(deal_contours[i]);
		rectangle(frame_mid, rect, Scalar(0, 255, 255), 1, 8);
	}
	
	//line(frame_mid, Point(100, 140), Point(100, 240), Scalar(0, 0, 255), 2);
	if (lines[5] == 1) 
	{
		line(frame_mid, Point(lines[1], lines[2]), Point(lines[3], lines[4]), Scalar(12, 200, 2), 2);
	}
	if (lines[10] == 1)
	{
		line(frame_mid, Point(lines[6], lines[7]), Point(lines[8], lines[9]), Scalar(12, 200, 2), 2);
	}
	CString mid_value;
	CString mid_value2;
	mid_value.Format(L"%d", this_back->count);
	mid_value2.Format(L"%d", this_back->count2);
	this_back->show_text.SetWindowTextW(mid_value);
	this_back->show_text2.SetWindowTextW(mid_value2);
	imshow("vehicle", frame_mid);
}


