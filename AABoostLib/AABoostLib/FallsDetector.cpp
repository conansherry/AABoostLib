#include "FallsDetector.h"

FallsDetector::FallsDetector()
{
	//���캯��
	Init();
}

FallsDetector::~FallsDetector()
{
	//��������
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

void FallsDetector::SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives,UINT maxweakclassifiernum)
{
	m_maxfalsepositivesf=maxfalsepositives;
	m_minpassd=minpass;
	m_targetfalsepositivesf=targetfalsepositives;
	m_maxweakclassifiernum=maxweakclassifiernum;
}

void FallsDetector::LoadSamples()
{
	//��������
}

void FallsDetector::LevelTrain()
{
	m_aaboost.RunRealAdaboost(m_maxfalsepositivesf,m_minpassd,m_maxweakclassifiernum);
	m_cascadeclassifier.push_back(m_aaboost);
	m_cascadeclassifier.back().Release();
}

void FallsDetector::LevelTrainFinished()
{
	m_fi=m_maxfalsepositivesf*m_fi;
	m_i++;
	NegSamples().swap(m_negsamples);

	if(m_fi>m_targetfalsepositivesf)
	{
		//�ռ��µ�����������

		//�õ�ǰ�ٲ�ɨ��������

		//�õ�ǰ�ٲ�ɨ�踺����
	}
}

void FallsDetector::CreateCascadeClassifier()
{
	Init();

	//���õ�һ�����

	while(m_fi>m_targetfalsepositivesf)
	{
		LevelTrain();
		
		LevelTrainFinished();

		//������һ�����
	}
}