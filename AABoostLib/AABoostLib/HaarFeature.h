#ifndef HAARFEATURE_H
#define HAARFEATURE_H

#include "Common.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace std;

class EXPORT_CLASS HaarFeature
{
	//��Ϊ
public:
	HaarFeature();
	~HaarFeature();

	void ExtractHaarFeatures(const cv::Mat &image);
	void ExtractHaarFeatures(const cv::Mat &image,vector<double> &features);

	//��Ϊ
private:
	//��ʼ������
	void Init(unsigned int Width=0,unsigned int Height=0,unsigned int MinArea=0);

	//�������ͼ
	void CalcIntegralImage(const cv::Mat &image);

	//����Haar����
	void ExtractFeatures();

	//�����������
	void Clean();

	//��ԪHaar��������
	double CalcHaarFeature(unsigned int x0,unsigned int y0,unsigned int width0,unsigned int height0,int coefficient0,
	                       unsigned int x1,unsigned int y1,unsigned int width1,unsigned int height1,int coefficient1);

	//����
public:
	vector<double> m_features;

	//����
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_minarea;

	cv::Mat m_sum;
};

#endif