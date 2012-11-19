#include "FallsDetector.h"
#include "HaarFeature.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

FallsDetector::FallsDetector()
{
	//构造函数
	Init();
}

FallsDetector::~FallsDetector()
{
	//析构函数
}

void FallsDetector::Init()
{
	m_i=1;
	m_fi=1;

	m_maxfalsepositivesf=0;
	m_minpassd=0;
	m_targetfalsepositivesf=0;
	m_maxweakclassifiernum=0;
}

void FallsDetector::SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives,unsigned int maxweakclassifiernum)
{
	Init();

	m_maxfalsepositivesf=maxfalsepositives;
	m_minpassd=minpass;
	m_targetfalsepositivesf=targetfalsepositives;
	m_maxweakclassifiernum=maxweakclassifiernum;
}

void FallsDetector::LevelTrain()
{
	m_aaboost.RunRealAdaboost(m_maxfalsepositivesf,m_minpassd,m_maxweakclassifiernum);
}

void FallsDetector::LevelTrainFinished()
{
	m_fi=m_aaboost.m_falsepositivesf*m_fi;
	m_i++;
	m_negsamples.clear();

	if(m_fi>m_targetfalsepositivesf)
	{
		//收集新的正、负样本

		//用当前瀑布扫描正样本

		//用当前瀑布扫描负样本
	}
}

void FallsDetector::CreateCascadeClassifier(string posfile,string negfile)
{
	//设置第一层参数

	while(m_fi>m_targetfalsepositivesf)
	{
		//挑选样本
		//if(m_i==1)
		//	PrepareSamples(posfile,negfile);
		if(m_i==1)
			LoadSamples("D:/WorkPlace/samples/POSDATA2","D:/WorkPlace/samples/NEGDATA2");

		LevelTrain();
		
		LevelTrainFinished();

		//第一层训练完毕就退出(测试)
		break;

		//设置下一层参数
	}
}

void FallsDetector::PrepareSamples(string posfile,string negfile)
{
	ifstream fin;
	ofstream fout;
	HaarFeature haarfeature;
	string filepath;
	unsigned int total;

	//载入正样本
	fin.open(posfile,ios_base::in);
	if(!fin.is_open())
	{
#ifdef DEBUG_OUTPUT
		cout<<"Open File Error"<<endl;
#endif
		exit(1);
	}

	fout.open("D:/WorkPlace/samples/POSDATA1",ios_base::out|ios_base::binary);
	if(!fout.is_open())
	{
#ifdef DEBUG_OUTPUT
		cout<<"Open File Error"<<endl;
#endif
		exit(1);
	}

	m_aaboost.Release();
	total=0;
	while(total<10000 && getline(fin,filepath))
	{
		cv::Mat pos=cv::imread(filepath,0);
		if(!pos.empty() && pos.cols==20 && pos.rows==20)
		{
			haarfeature.ExtractHaarFeatures(pos);
			//m_aaboost.InsertOneSample(OneSample::POSITIVE,haarfeature.m_features);
			SaveFeatures(fout,haarfeature.m_features);
			total++;
#ifdef DEBUG_OUTPUT
			cout<<"保存新正样本:"<<total<<endl;
#endif
		}
	}

#ifdef DEBUG_OUTPUT
		cout<<"插入正样本完毕，总数:"<<total<<endl;
#endif

	fin.close();
	fout.close();

	//载入负样本(随机载入)
	fin.open(negfile,ios_base::in);
	if(!fin.is_open())
	{
#ifdef DEBUG_OUTPUT
		cout<<"Open File Error"<<endl;
#endif
		exit(1);
	}

	fout.open("D:/WorkPlace/samples/NEGDATA1",ios_base::out|ios_base::binary);
	if(!fout.is_open())
	{
#ifdef DEBUG_OUTPUT
		cout<<"Open File Error"<<endl;
#endif
		exit(1);
	}

	vector<string> neglist;
	while(getline(fin,filepath))
	{
		neglist.push_back(filepath);
	}

	total=0;
	while(total<10000)
	{
		int position=(int)((double)(neglist.size()-1)*rand()/RAND_MAX);
		cv::Mat neg=cv::imread(neglist[position],0);
		if(!neg.empty() && neg.cols==20 && neg.rows==20)
		{
			haarfeature.ExtractHaarFeatures(neg);
			//m_aaboost.InsertOneSample(OneSample::NEGATIVE,haarfeature.m_features);
			SaveFeatures(fout,haarfeature.m_features);
			total++;
#ifdef DEBUG_OUTPUT
			cout<<"保存新负样本:"<<total<<endl;
#endif
		}
	}
#ifdef DEBUG_OUTPUT
		cout<<"插入负样本完毕，总数:"<<total<<endl;
#endif

	fin.close();
	fout.close();
}

void FallsDetector::SaveFeatures(ofstream &fout,vector<double> &features)
{
	vector<double>::iterator itr;
	double *tmp=new double [features.size()];
	unsigned int idx;
	for(itr=features.begin(),idx=0;itr!=features.end();itr++,idx++)
	{
		tmp[idx]=*itr;
	}
	//写文件
}

void FallsDetector::LoadSamples(string posdata,string negdata)
{
	//const unsigned int featuresnum=100;
	const unsigned int featuresnum=221;
	const unsigned int samplesnum=15000;
	unsigned int old_total;
	unsigned int total;
	ifstream fin;

	fin.open(posdata,ios_base::in);
	if(!fin.is_open())
	{
#ifdef DEBUG_OUTPUT
		cout<<"Open File Error"<<endl;
#endif
		exit(1);
	}
	
	m_aaboost.Release();
	m_aaboost.m_allsamples.reserve(samplesnum*2);
	for(total=0;total<samplesnum;total++)
	{
		vector<double> vfeat;
		vfeat.resize(featuresnum);

		clock_t start,finish;
		start=clock();
		for(unsigned int featnum=0;featnum<featuresnum;featnum++)
		{
			double features;
			fin>>features;
			vfeat[featnum]=features;
		}
		m_aaboost.InsertOneSample(OneSample::POSITIVE,vfeat);
		finish=clock();
#ifdef DEBUG_OUTPUT
		cout<<"\r插入第"<<setw(10)<<m_aaboost.m_allsamples.size()<<"个正样本. 耗时:"<<setw(8)<<(double)(finish-start)/CLOCKS_PER_SEC<<"秒";
#endif
	}
	fin.close();
#ifdef DEBUG_OUTPUT
		cout<<endl;
#endif

	fin.open(negdata,ios_base::in);
	if(!fin.is_open())
	{
#ifdef DEBUG_OUTPUT
		cout<<"Open File Error"<<endl;
#endif
		exit(1);
	}

	old_total=total;
	for(total=0;total<samplesnum;total++)
	{
		vector<double> vfeat;
		vfeat.resize(featuresnum);

		clock_t start,finish;
		start=clock();
		for(unsigned int featnum=0;featnum<featuresnum;featnum++)
		{
			double features;
			fin>>features;
			vfeat[featnum]=features;
		}
		m_aaboost.InsertOneSample(OneSample::NEGATIVE,vfeat);
		finish=clock();
#ifdef DEBUG_OUTPUT
		cout<<"\r插入第"<<setw(10)<<m_aaboost.m_allsamples.size()-samplesnum<<"个负样本. 耗时:"<<setw(8)<<(double)(finish-start)/CLOCKS_PER_SEC<<"秒";
#endif
	}
	fin.close();
#ifdef DEBUG_OUTPUT
		cout<<endl;
#endif
}