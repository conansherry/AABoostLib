#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include "Common.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class EXPORT_CLASS BackGround
{
	//行为
public:
	BackGround();
	~BackGround();

	//行为
private:
	//初始化参数
	void Init(double scale=0,double scalefactor=0);

	//载入图片路径文件
	void LoadPictures(string srcfilename);

	//设置负样本输出路径
	void SetOutputDir(string outputdir);

	//输出负样本
	void OutputBackground();

	//属性
private:
	unsigned int m_total;
	double m_scale;
	double m_scalefactor;

	cv::Mat m_input;
	cv::Mat m_output;
	cv::Rect m_bgroi;

	string m_srcfilename;
	string m_outputdir;
};

#endif