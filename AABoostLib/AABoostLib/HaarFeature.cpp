#include "HaarFeature.h"

HaarFeature::HaarFeature()
{
	//构造函数
	Init();
}

HaarFeature::~HaarFeature()
{
	//析构函数
}

void HaarFeature::Init(unsigned int Width,unsigned int Height,unsigned int MinArea)
{
	m_width=Width;
	m_height=Height;
	m_minarea=MinArea;
}

void HaarFeature::CalcIntegralImage(const cv::Mat &image)
{
	m_sum.create(image.rows+1,image.cols+1,CV_64FC1);
	cv::integral(image,m_sum,CV_64F);
}

void HaarFeature::ExtractFeatures()
{
	unsigned int x,y,dx,dy;
	for(x=0;x<m_width;x++)
		for(y=0;y<m_height;y++)
			for(dx=1;dx<=m_width;dx++)
				for(dy=1;dy<=m_height;dy++)
				{
					//类型1
					if((x+dx*2<=m_width) && (y+dy<=m_height))
					{
						if(dx*2*dy<m_minarea)
							continue;

						//计算特征
						double feature;
						feature=CalcHaarFeature(x,		y,	dx*2,	dy,	-1,
							                    x+dx,	y,	dx,		dy,	+2);
						m_features.push_back(feature);
					}

					//类型2
					if((x+dx<=m_width) && (y+dy*2<=m_height))
					{
						if(dx*2*dy<m_minarea)
							continue;

						//计算特征
						double feature;
						feature=CalcHaarFeature(x,	y,		dx,	dy*2,	-1,
							                    x,	y+dy,	dx,	dy,		+2);
						m_features.push_back(feature);
					}

					//类型3
					if((x+dx*3<=m_width) && (y+dy<=m_height))
					{
						if(dx*3*dy<m_minarea)
							continue;

						//计算特征
						double feature;
						feature=CalcHaarFeature(x,		y,	dx*3,	dy,	+1,
							                    x+dx,	y,	dx,		dy,	-2);
						m_features.push_back(feature);
					}

					//类型4
					if((x+dx*2<=m_width) && (y+dy*2<=m_height))
					{
						if(dx*2*dy*2<m_minarea)
							continue;

						//计算特征
						double feature;
						feature=CalcHaarFeature(x,	y,	dx*2,	dy*2,	+1,
							                    x,	y,	dx,		dy,		-4)
								+
								CalcHaarFeature(x,		y,		dx*2,	dy*2,	+1,
								                x+dx,	y+dy,	dx,		dy,		-4);
						feature/=2;
						m_features.push_back(feature);
					}

					//类型5
					if((x+dx*2<=m_width) && (y+dy*2<=m_height))
					{
						if(dx*2*dy*2<m_minarea)
							continue;

						//计算特征
						double feature;
						feature=CalcHaarFeature(x,		y+dy,	dx,	dy,	+1,
							                    x+dx,	y,		dx,	dy,	-1);
						m_features.push_back(feature);
					}

					//类型6
					if((x+dx*2<=m_width) && (y+dy*2<=m_height))
					{
						if(dx*2*dy*2<m_minarea)
							continue;

						//计算特征
						double feature;
						feature=CalcHaarFeature(x,		y,		dx,	dy,	-1,
							                    x+dx,	y+dy,	dx,	dy,	+1);
						m_features.push_back(feature);
					}
				}
}

double HaarFeature::CalcHaarFeature(unsigned int x0,unsigned int y0,unsigned int width0,unsigned int height0,int coefficient0,
	                                unsigned int x1,unsigned int y1,unsigned int width1,unsigned int height1,int coefficient1)
{
	double value1,value2;

	value1=m_sum.at<double>(x0,y0)+m_sum.at<double>(x0+width0,y0+height0)-m_sum.at<double>(x0+width0,y0)-m_sum.at<double>(x0,y0+height0);
	value1*=coefficient0;

	value2=m_sum.at<double>(x1,y1)+m_sum.at<double>(x1+width1,y1+height1)-m_sum.at<double>(x1+width1,y1)-m_sum.at<double>(x1,y1+height1);
	value2*=coefficient1;

	return (value1+value2);
}

void HaarFeature::Clean()
{
	vector<double>().swap(m_features);
}