#ifndef HOGFEATURE_H
#define HOGFEATURE_H

#include "Common.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>

using namespace std;

class EXPORT_CLASS HogFeature
{
	//行为
public:
	HogFeature();
	~HogFeature();

	void CreateHogDescriptor(cv::Size win_size=cv::Size(64,128),cv::Size block_size=cv::Size(16,16),cv::Size block_stride=cv::Size(8,8),cv::Size cell_size=cv::Size(8,8),int nbins=9);

	void ExtractHaarFeatures(const cv::Mat &image,cv::Size winStride);
	void ExtractHaarFeatures(const cv::Mat &image,cv::Size winStride,vector<double> &features);

	unsigned int GetFeaturesDim();

	//行为
private:
	void Init();
	
	//属性
public:
	vector<double> m_features;

	//属性
private:
	cv::HOGDescriptor *m_cpuhog;
};

#endif