#include "FallsDetector.h"

FallsDetector::FallsDetector()
{
	//���캯��
	m_i=1;
	m_Fi=1;

	m_maxfalsepositivesf=0;
	m_minpassd=0;
	m_targetfalsepositivesf=0;
}

FallsDetector::~FallsDetector()
{
	//��������
}

void FallsDetector::SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives)
{
	m_maxfalsepositivesf=maxfalsepositives;
	m_minpassd=minpass;
	m_targetfalsepositivesf=targetfalsepositives;
}

void FallsDetector::LoadSamples()
{
}

void FallsDetector::LevelTrain()
{
}

void FallsDetector::LevelTrainFinished()
{
}