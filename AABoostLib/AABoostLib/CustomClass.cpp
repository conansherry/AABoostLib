#include "CustomClass.h"
#include <math.h>

OneSample::OneSample()
{
	//构造函数
	m_label=OneSample::POSITIVE;
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
	m_h=0;
}

DividedManagement::~DividedManagement()
{
	//析构函数
}

void DividedManagement::CalcProbW()
{
	Samples::iterator itr;
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

void DividedManagement::CalcH()
{
	m_h=(double)0.5*log((m_probposw+m_smoothingfactor)/(m_probnegw+m_smoothingfactor));
}

double DividedManagement::GetH()
{
	return m_h;
}

void DividedManagement::SetSmoothingFactor(double value)
{
	m_smoothingfactor=value;
}

AABoost::AABoost()
{
	//构造函数
	m_bestclassifier=0;
	m_binscount=0;
	m_bestnormalizationfactor=-1;
	m_currentclassifier=0;
}

AABoost::~AABoost()
{
	//析构函数
}

void AABoost::Samples2Managements(CLASSIFIER classifier)
{
	m_dividedmanagements.resize(m_binscount);

	Samples::iterator itr;
	for(itr=m_allsamples.begin();itr!=m_allsamples.end();itr++)
	{
		uint32_t xi=(uint32_t)(itr->m_features[classifier]*m_binscount);
		m_dividedmanagements[xi].m_samples.push_back(*itr);
	}

	Samples().swap(m_allsamples);
}

void AABoost::Managements2Samples()
{
	DividedManagements::iterator itr;
	for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
	{
		Samples::iterator sitr;
		for(sitr=itr->m_samples.begin();sitr!=itr->m_samples.end();sitr++)
		{
			m_allsamples.push_back(*sitr);
		}
	}

	DividedManagements().swap(m_dividedmanagements);
}

void AABoost::CalcBestNormalizationFactor()
{
	double normalizationfactor=0;
	double posw,negw;
	DividedManagements::iterator itr;
	for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
	{
		itr->CalcProbW();
		posw=itr->GetProbPosW();
		negw=itr->GetProbNegW();
		normalizationfactor+=(double)2.0*sqrt(posw*negw);
	}

	if(m_bestnormalizationfactor<0)
	{
		m_bestnormalizationfactor=normalizationfactor;
	}
	else
	{
		if(m_bestnormalizationfactor>normalizationfactor)
		{
			m_bestnormalizationfactor=normalizationfactor;
			m_bestclassifier=m_currentclassifier;
		}
	}
}

void AABoost::UpdateProbabilityDistribution()
{
	DividedManagements::iterator itr;
	for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
	{
		Samples::iterator sitr;
		for(sitr=itr->m_samples.begin();sitr!=itr->m_samples.end();sitr++)
		{
			sitr->m_probability=sitr->m_probability*exp(-(sitr->m_label)*(itr->GetH()))/m_bestnormalizationfactor;
		}
	}
}