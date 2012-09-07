#include "BackGround.h"

BackGround::BackGround()
{
	//构造函数
	Init();
}

BackGround::~BackGround()
{
	//析构函数
}

void BackGround::Init(double scale,double scalefactor)
{
	m_scale=scale;
	m_scalefactor=scalefactor;
}

void BackGround::LoadPictures(string srcfilename)
{
	m_srcfilename=srcfilename;
}

void BackGround::SetOutputDir(string outputdir)
{
	m_outputdir=outputdir;
}

void BackGround::OutputBackground()
{
}