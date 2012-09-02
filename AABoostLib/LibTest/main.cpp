#include "HaarFeature.h"
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
	HaarFeature haarfeature;
	cv::Mat img=cv::imread("face.jpg",0);
	haarfeature.ExtractHaarFeatures(img);
	cout<<haarfeature.m_features.size()<<endl;
	system("pause");
	return 0;
}