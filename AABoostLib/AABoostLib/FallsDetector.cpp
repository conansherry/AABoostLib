#include "FallsDetector.h"

FallsDetector::FallsDetector()
{
	//构造函数
	m_i=0;
	m_Fi=0;

	m_maxfalsepositivesf=0;
	m_minpassd=0;
	m_targetfalsepositivesf=0;
}

FallsDetector::~FallsDetector()
{
	//析构函数
}

void FallsDetector::SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives)
{
	m_maxfalsepositivesf=maxfalsepositives;
	m_minpassd=minpass;
	m_targetfalsepositivesf=targetfalsepositives;
}