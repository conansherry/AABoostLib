#include "HaarFeature.h"
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
	HaarFeature haarfeature;
	cv::Mat img=cv::imread("face.jpg",0);
	haarfeature.Init(img.cols,img.rows);
	haarfeature.CalcIntegralImage(img);
	haarfeature.ExtractFeatures();
	cout<<haarfeature.m_features.size()<<endl;
	system("pause");
	return 0;
}