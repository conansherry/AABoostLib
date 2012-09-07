#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include "Common.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class EXPORT_CLASS BackGround
{
	//��Ϊ
public:
	BackGround();
	~BackGround();

	//��Ϊ
private:
	//��ʼ������
	void Init(double scale=0,double scalefactor=0);

	//����ͼƬ·���ļ�
	void LoadPictures(string srcfilename);

	//���ø��������·��
	void SetOutputDir(string outputdir);

	//���������
	void OutputBackground();

	//����
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