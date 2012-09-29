#include "BackGround.h"
#include <fstream>

BackGround::BackGround()
{
	//构造函数
}

BackGround::~BackGround()
{
	//析构函数
}

void BackGround::Init(int width,int height)
{
	m_total=0;

	m_bgroi.width=width;
	m_bgroi.height=height;
}

void BackGround::LoadPictures(string srcfilename)
{
	m_srcfilename=srcfilename;
}

void BackGround::SetOutputDir(string outputdir)
{
	m_outputdir=outputdir;
}

void BackGround::OutputBackground(double scale,double scalefactor,double step)
{
	cv::Rect currentroi;
	currentroi.width=m_bgroi.width;
	currentroi.height=m_bgroi.height;
	for(;currentroi.width<m_input.cols || currentroi.height<m_input.rows;)
	{
		currentroi.x=0;
		currentroi.y=0;
		for(;currentroi.x+currentroi.width<m_input.cols;currentroi.x=(int)(currentroi.x+currentroi.width*step))
		{
			for(;currentroi.y+currentroi.height<m_input.rows;currentroi.y=(int)(currentroi.y+currentroi.height*step))
			{
				cv::Mat imgtmp=m_input(currentroi);
				cv::Mat imgtmp_target(m_bgroi.height,m_bgroi.width,m_input.type());
				cv::resize(imgtmp,imgtmp_target,cv::Size(m_bgroi.width,m_bgroi.height));

				char num[NUMLENGTH];
#ifdef WIN32
				_itoa_s(m_total++,num,10);
#else
				itoa(m_total++,num,10);
#endif
				string strnum(num);
				cv::imwrite(m_outputdir+m_prefix+string("_")+strnum+string(".jpg"),imgtmp_target);
			}
		}
		currentroi.width=(int)(m_bgroi.width*scale);
		currentroi.height=(int)(m_bgroi.height*scale);
		scale*=scalefactor;
	}
}

void BackGround::SetPrefix(string prefix)
{
	m_prefix=prefix;
}

string BackGround::GetFileName(const char *fullname)
{
	string filename=fullname;
	const char *p_first=fullname;
	const char *p_last=fullname+strlen(fullname);
	if(strrchr(fullname,'\\')!=NULL)
		p_first=strrchr(fullname,'\\')+1;
	else if(strrchr(fullname,'/')!=NULL)
		p_first=strrchr(fullname,'/')+1;
	if(strrchr(fullname,'.')!=NULL)
		p_last=strrchr(fullname,'.');
	if(p_last<p_first)
		p_last=fullname+strlen(fullname);

	filename.assign(p_first,p_last);

	return filename;
}

void BackGround::GetBackground(string srcfilename,string outputdir,unsigned int width,unsigned int height,double scale,double scalefactor,double step)
{
	Init(width,height);
	LoadPictures(srcfilename);
	SetOutputDir(outputdir);

	string filepath;
	ifstream fin(m_srcfilename,ios_base::in);
	if(!fin.is_open())
	{
#ifdef DEBUG_OUTPUT
		cout<<"Open File Error"<<endl;
#endif
		exit(1);
	}
	while(getline(fin,filepath))
	{
		m_input.release();
		m_input=cv::imread(filepath,0);
		SetPrefix(GetFileName(filepath.c_str()));
		OutputBackground(scale,scalefactor,step);
	}
	fin.close();
}