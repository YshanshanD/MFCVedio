#include "stdafx.h"
// MyTools.cpp : ʵ���ļ�
//

#include "MyTools.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MyTools::MyTools()
{

}

Mat MyTools::getPictureBackground(VideoCapture& capture, int order)
{
	Mat mid,mmid,middle;
	if (!capture.read(mid)) return mid;
	cvtColor(mid, mid, COLOR_BGR2GRAY);
	absdiff(mid, mid, mid);
	for (int i = 0; i < 50; i++) {
		if (!capture.read(mmid)) break;
		cvtColor(mmid, mmid, COLOR_BGR2GRAY);
		addWeighted(mid, 1, mmid, 0.02, 0, mid);
	}
	//mmid = mmid / 30;
	capture.set(CV_CAP_PROP_POS_FRAMES, order);
	return mid;
}
