#include "RealAdaboost.h"
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

LUT::LUT()
{
	//构造函数
	m_binscount=0;
	m_feattypesnum=0;
}

LUT::~LUT()
{
	//析构函数
}

void LUT::GetMinMaxFeat(Samples &allsamples)
{
	double min,max;
	vector<double>().swap(m_min);
	vector<double>().swap(m_max);

	if(allsamples.size()>0)
	{
		CLASSIFIER classifier;
		for(classifier=0;classifier=m_feattypesnum;classifier++)
		{
			Samples::iterator sitr;
			for(sitr=allsamples.begin();sitr!=allsamples.end();sitr++)
			{
				if(sitr==allsamples.begin())
				{
					min=sitr->m_features[classifier];
					max=sitr->m_features[classifier];
				}
				else
				{
					if(min>sitr->m_features[classifier])
					{
						min=sitr->m_features[classifier];
					}
					else if(max<sitr->m_features[classifier])
					{
						max=sitr->m_features[classifier];
					}
				}
			}

			m_min.push_back(min);
			m_max.push_back(max);
		}
	}
}

void LUT::SetBinsCount(INT binscount)
{
	m_binscount=binscount;
}

INT LUT::GetBinsCount()
{
	return m_binscount;
}

INT LUT::FindFeatBin(CLASSIFIER classifier,double feature)
{
	if(m_min.size()>0 && m_max.size()>0 && m_min.size()==m_max.size())
	{
		if(feature<m_min[classifier])
			feature=m_min[classifier];
		else if(feature>m_max[classifier])
			feature=m_max[classifier];

		INT bin=(INT)(0.5+m_binscount*(feature-m_min[classifier])/(m_max[classifier]-m_min[classifier]));
		return bin;
	}
	else
	{
		return m_binscount+1;
	}
}

void LUT::SetFeatTypesnum(UINT value)
{
	m_feattypesnum=value;
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
	m_bestnormalizationfactor=-1;
	m_currentclassifier=0;
	m_t=1;
}

AABoost::~AABoost()
{
	//析构函数
}

void AABoost::Samples2Managements(CLASSIFIER classifier)
{
	DividedManagements().swap(m_dividedmanagements);
	m_dividedmanagements.resize(m_binscount);

	Samples::iterator itr;
	for(itr=m_allsamples.begin();itr!=m_allsamples.end();itr++)
	{
		m_dividedmanagements[FindFeatBin(classifier,itr->m_features[classifier])].m_samples.push_back(*itr);
	}
}

void AABoost::Managements2Samples()
{
	Samples().swap(m_allsamples);

	DividedManagements::iterator itr;
	for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
	{
		Samples::iterator sitr;
		for(sitr=itr->m_samples.begin();sitr!=itr->m_samples.end();sitr++)
		{
			m_allsamples.push_back(*sitr);
		}
	}
}

void AABoost::SelectBestNormalizationFactorAndH()
{
	double normalizationfactor=0;
	double posw,negw;
	DividedManagements::iterator itr;
	for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
	{
		//计算 W+1 W-1
		itr->CalcProbW();
		posw=itr->GetProbPosW();
		negw=itr->GetProbNegW();

		//当前划分下，每个划分对应的弱分类器输出
		itr->CalcH();

		//计算归一化因子Z
		normalizationfactor+=(double)2.0*sqrt(posw*negw);
	}

	if(m_bestnormalizationfactor<0)
	{
		m_bestnormalizationfactor=normalizationfactor;
		
		//保存初始弱分类器输出
		vector<double>().swap(m_besth);
		for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
		{
			m_besth.push_back(itr->GetH());
		}
	}
	else
	{
		if(m_bestnormalizationfactor>normalizationfactor)
		{
			m_bestnormalizationfactor=normalizationfactor;

			//保存最优弱分类器输出
			vector<double>().swap(m_besth);
			for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
			{
				m_besth.push_back(itr->GetH());
			}

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
			sitr->m_probability=sitr->m_probability*exp(-(sitr->m_label)*(m_besth[(itr-m_dividedmanagements.begin())]))/m_bestnormalizationfactor;
		}
	}
}

void AABoost::RunRealAdaboost()
{
	//连续Adaboost算法主循环

	//初始化
	vector<CLASSIFIER>().swap(m_strongbestclassifier);
	vector<vector<double> >().swap(m_strongbesth);

	//计算所有类型的特征集合中的最大值和最小值
	GetMinMaxFeat(m_allsamples);

	//初始化样本概率分布
	Samples::iterator sitr;
	for(sitr=m_allsamples.begin();sitr!=m_allsamples.end();sitr++)
	{
		sitr->InitProb(m_allsamples.size());
	}

	while(m_t<T)
	{
		//每次迭代开始

		//对所有特征进行划分并得到最优特征及对应弱分类器输出
		CLASSIFIER classifier;
		for(classifier=0;classifier<m_feattypesnum;classifier++)
		{
			//对每一个类型特征，进行样本划分
			Samples2Managements(classifier);

			//当前类型对应划分处理
			SelectBestNormalizationFactorAndH();
		}

		//更新样本概率分布
		UpdateProbabilityDistribution();

		//记录该次迭代的最优特征和划分所对应的弱分类器输出
		m_strongbestclassifier.push_back(m_bestclassifier);
		m_strongbesth.push_back(m_besth);

		m_t++;
	}
}