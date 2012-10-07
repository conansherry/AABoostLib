#include "HogFeature.h"

HogFeature::HogFeature()
{
	//构造函数
	Init();
}

HogFeature::~HogFeature()
{
	//析构函数
	if(m_cpuhog)
		delete m_cpuhog;
}

void HogFeature::Init()
{
	m_cpuhog=NULL;
}

void HogFeature::CreateHogDescriptor(cv::Size win_size,cv::Size block_size,cv::Size block_stride,cv::Size cell_size,int nbins)
{
	if(m_cpuhog)
	{
		delete m_cpuhog;
		m_cpuhog=NULL;
	}

	m_cpuhog=new cv::HOGDescriptor(win_size,block_size,block_stride,cell_size,nbins);
}

void HogFeature::ExtractHaarFeatures(const cv::Mat &image)
{
	m_features.clear();

	if(m_cpuhog)
	{
		vector<float> tmpfeatures;
		m_cpuhog->compute(image,tmpfeatures,cv::Size(1,1),cv::Size(0,0));
		m_features.assign(tmpfeatures.begin(),tmpfeatures.end());
	}
}

void HogFeature::ExtractHaarFeatures(const cv::Mat &image,vector<double> &features)
{
	features.clear();

	ExtractHaarFeatures(image);

	if(m_cpuhog)
	{
		features=m_features;
	}
}