#include "BackGround.h"

BackGround::BackGround()
{
	//���캯��
	Init();
}

BackGround::~BackGround()
{
	//��������
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