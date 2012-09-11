#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include <fstream>
#include "Common.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class EXPORT_CLASS BackGround
{
	//行为
public:
	BackGround();
	~BackGround();

	void GetBackground(string srcfilename,string outputdir,unsigned int width=20,unsigned int height=20,double scale=1.2,double scalefactor=1.2,double step=0.2);

	//行为
private:
	//初始化参数
	void Init(int width,int height);

	//载入图片路径文件
	void LoadPictures(string srcfilename);

	//设置负样本输出路径
	void SetOutputDir(string outputdir);

	//输出负样本
	void OutputBackground(double scale,double scalefactor,double step);

	//设置输出前缀
	void SetPrefix(string prefix);

	//获取不带文件路径和后缀的文件名
	string GetFileName(const char *fullname);

	//属性
private:
	unsigned int m_total;
	double m_scale;
	double m_scalefactor;
	double m_step;

	cv::Mat m_input;
	cv::Mat m_output;
	cv::Size m_bgroi;

	string m_srcfilename;
	string m_outputdir;
	string m_prefix;
};

#endif