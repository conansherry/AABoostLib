#include "FallsDetector.h"

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

void FallsDetector::SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives,double maxweakclassifiernum)
{
	m_maxfalsepositivesf=maxfalsepositives;
	m_minpassd=minpass;
	m_targetfalsepositivesf=targetfalsepositives;
	m_maxweakclassifiernum=maxweakclassifiernum;
}

void FallsDetector::LoadSamples()
{
	//载入样本
}

void FallsDetector::LevelTrain()
{
	m_aaboost.RunRealAdaboost(m_maxfalsepositivesf,m_minpassd,m_maxweakclassifiernum);
}

void FallsDetector::LevelTrainFinished()
{
	m_fi=m_maxfalsepositivesf*m_fi;
	m_i++;
	NegSamples().swap(m_negsamples);

	if(m_fi>m_targetfalsepositivesf)
	{
		//收集新的负样本
	}
}

void FallsDetector::CreateCascadeClassifier()
{
	Init();
}