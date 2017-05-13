#include "stdafx.h"
#include "PeopleDetector.h"
#include <string.h>
#include <ctype.h>
#include "MFCTest1Dlg.h"



PeopleDetector::PeopleDetector()
{
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
		HOGDescriptor hog;  //HOG����������
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());  //�õ�SVM�������----���ڶ�hog�������з����svmģ�͵�ϵ����ֵ

/*char _filename[1024]; //ͼ���ļ���
	   for (;;)
		{
			char* filename = _filename;
			if (f)
			{
				if (!fgets(filename, (int)sizeof(_filename) - 2, f))  //���ļ�ָ���ж�ȡn-1���ַ����浽��sΪ��ʼ��ַ�Ŀռ��ֱ������һ�У�����ɹ��򷵻�s��ָ�룬���򷵻�NULL��
					break;
				//while(*filename && isspace(*filename))
				//	++filename;
				if (filename[0] == '#') //�����һ���ַ��ǡ�#�������ʾע��
					continue;
				int l = strlen(filename);
				while (l > 0 && isspace(filename[l - 1]))
					--l;
				filename[l] = '\0';
				img = imread(filename);
			}
			printf("%s:\n", filename);
			if (!img.data)
				continue;

			fflush(stdout);  //���������
			*/



			vector<Rect> found, found_filtered;
			double t = (double)getTickCount();  //�Ӳ���ϵͳ�����������������ĺ�����
			int can = img.channels();  //��ȡͨ����

		   /*������HOGDescriptor::detectMultiScale(const GpuMat& img, vector<Rect>& found_locations, double hit_threshold=0,
		    Size win_stride=Size(), Size padding=Size(), double scale0=1.05, int group_threshold=2)
            ���ܣ��������ͼƬimg���ж�߶ȵ����˼��.
			����˵����
			img�����������ͼƬ
			found_locations����⵽��Ŀ�������б�
			hit_threshold�������ڲ�Ϊ��������Ŀ�����ֵ��Ҳ���Ǽ�⵽��������SVM���೬ƽ��ľ���
            win_stride����������ÿ���ƶ��ľ��루�����ǿ��ƶ����������� padding��ͼ������Ĵ�С
			scale0������ϵ��������������ÿ�����ӵı���
			group_threshold��У��ϵ������һ��Ŀ�걻������ڼ�����ʱ�����������.����Ϊ0�ǲ�����*/

			hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);

			t = (double)getTickCount() - t;  //������ķѵ�ʱ��
			printf("tdetection time = %gms\n", t*1000. / cv::getTickFrequency()); //�ڳ���εĿ�ʼ�ͽ���ʱ����ʹ��cvGetTickCount()��Ȼ�����εĲ����
																				  //cvGetTickFrequency()��Ϳ��Ի�ó���ε���΢��usΪ��λ������ʱ��
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

			//�����ο�
			for (i = 0; i < found_filtered.size(); i++)
			{
				Rect r = found_filtered[i];
				// ��ΪHOG detector���ص��±�Ŀ���ľ��ο����Ӧ��С���ο�
				r.x += cvRound(r.width*0.1);
				r.width = cvRound(r.width*0.8);
				r.y += cvRound(r.height*0.07);
				r.height = cvRound(r.height*0.8);
				rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);  //img-ͼƬ��tl----the top-left corner��br----the top-left corner��Scalar()-���ο���ɫ��config6-�߿�
				
			}
			resize(img, img, Size(this_back->picture_y, this_back->picture_x));
			line(img,Point(150,180),Point(150,200),Scalar(99,100,33),2);
			line(img, Point(280, 180), Point(280, 200), Scalar(99, 100, 33),2);
			imshow("vehicle", img);
			int c = waitKey(1);  
		} 
		




