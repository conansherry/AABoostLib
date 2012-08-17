#include "CustomClass.h"
#include <math.h>

OneSample::OneSample()
{
	//构造函数
	m_label=0;
	m_partition=0;
	m_probability=0;
}

OneSample::~OneSample()
{
	//析构函数
}

void OneSample::InitProb(unsigned int samplesNum)
{
	m_probability=(double)1.0/samplesNum;
}

DividedManagement::DividedManagement()
{
	//构造函数
	m_probposw=0;
	m_probnegw=0;
	m_output=0;
}

DividedManagement::~DividedManagement()
{
	//析构函数
}

void DividedManagement::CalcProbW()
{
	vector<OneSample>::iterator itr;
	m_probposw=0;
	m_probnegw=0;
	for(itr=m_samples.begin();itr!=m_samples.end();itr++)
	{
		if(itr->m_label==OneSample::POSITIVE)
		{
			m_probposw+=itr->m_probability;
		}
		else if(itr->m_label==OneSample::NEGATIVE)
		{
			m_probnegw+=itr->m_probability;
		}
	}
}

double DividedManagement::GetProbPosW()
{
	return m_probposw;
}

double DividedManagement::GetProbNegW()
{
	return m_probnegw;
}

void DividedManagement::CalcOutput()
{
	m_output=(double)0.5*log((m_probposw+m_smoothingfactor)/(m_probnegw+m_smoothingfactor));
}

double DividedManagement::GetOutput()
{
	return m_output;
}

void DividedManagement::SetSmoothingFactor(double value)
{
	m_smoothingfactor=value;
}