#ifndef HAARFEATURE_H
#define HAARFEATURE_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace std;

class HaarFeature
{
	//��Ϊ
public:
	HaarFeature();
	~HaarFeature();

	//��ʼ������
	void Init(unsigned int Width,unsigned int Height,unsigned int MinArea);

	//�������ͼ
	void CalcIntegralImage(const cv::Mat &image);

	//����Haar����
	void ExtractFeatures();

	//��ԪHaar��������
	double CalcHaarFeature(unsigned int x0,unsigned int y0,unsigned int width0,unsigned int height0,int coefficient0,
	                       unsigned int x1,unsigned int y1,unsigned int width1,unsigned int height1,int coefficient1);

	//�����������
	void Clean();

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