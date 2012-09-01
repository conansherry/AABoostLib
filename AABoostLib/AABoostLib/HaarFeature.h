#ifndef HAARFEATURE_H
#define HAARFEATURE_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace std;

class HaarFeature
{
	//行为
public:
	HaarFeature();
	~HaarFeature();

	//初始化参数
	void Init(unsigned int Width,unsigned int Height,unsigned int MinArea);

	//计算积分图
	void CalcIntegralImage(const cv::Mat &image);

	//生成Haar特征
	void ExtractFeatures();

	//单元Haar特征计算
	double CalcHaarFeature(unsigned int x0,unsigned int y0,unsigned int width0,unsigned int height0,int coefficient0,
	                       unsigned int x1,unsigned int y1,unsigned int width1,unsigned int height1,int coefficient1);

	//清空特征集合
	void Clean();

	//属性
public:
	vector<double> m_features;

	//属性
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_minarea;

	cv::Mat m_sum;
};

#endif