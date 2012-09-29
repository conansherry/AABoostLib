#include "RealAdaboost.h"
#include <math.h>
#include <algorithm>

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
	m_min.clear();
	m_max.clear();

	if(allsamples.size()>0)
	{
		SetFeatTypesnum(allsamples[0].m_features.size());

		CLASSIFIER classifier;
		for(classifier=0;classifier<m_feattypesnum;classifier++)
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

void LUT::SetBinsCount(int binscount)
{
	m_binscount=binscount;
}

int LUT::GetBinsCount()
{
	return m_binscount;
}

int LUT::FindFeatBin(CLASSIFIER classifier,double feature)
{
	if(m_min.size()>0 && m_max.size()>0 && m_min.size()==m_max.size())
	{
		if(feature<m_min[classifier])
			feature=m_min[classifier];
		else if(feature>m_max[classifier])
			feature=m_max[classifier];

		int bin=(int)((m_binscount-1)*(feature-m_min[classifier])/(m_max[classifier]-m_min[classifier]));
		return bin;
	}
	else
	{
		return m_binscount;
	}
}

void LUT::SetFeatTypesnum(unsigned int value)
{
	m_feattypesnum=value;
}

unsigned int LUT::GetFeatTypesnum()
{
	return m_feattypesnum;
}

DividedManagement::DividedManagement()
{
	//构造函数
	m_probposw=0;
	m_probnegw=0;
	m_h=0;
	m_smoothingfactor=0.000001;
}

DividedManagement::~DividedManagement()
{
	//析构函数
}

void DividedManagement::CalcProbW()
{
	PSamples::iterator itr;
	m_probposw=0;
	m_probnegw=0;
	for(itr=m_samples.begin();itr!=m_samples.end();itr++)
	{
		if((*itr)->m_label==OneSample::POSITIVE)
		{
			m_probposw+=(*itr)->m_probability;
		}
		else if((*itr)->m_label==OneSample::NEGATIVE)
		{
			m_probnegw+=(*itr)->m_probability;
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
	Init();
}

AABoost::~AABoost()
{
	//析构函数
}

void AABoost::Init()
{
	m_bestclassifier=0;
	m_bestnormalizationfactor=-1;
	m_currentclassifier=0;
	m_t=0;
	m_finalclassifier.m_bestb=0;
}

void AABoost::InitWeak()
{
	m_bestclassifier=0;
	m_bestnormalizationfactor=-1;
	m_currentclassifier=0;
}

void AABoost::Samples2Managements(CLASSIFIER classifier)
{
	m_dividedmanagements.clear();
	m_dividedmanagements.resize(m_finalclassifier.GetBinsCount());

	Samples::iterator itr;
	for(itr=m_allsamples.begin();itr!=m_allsamples.end();itr++)
	{
		m_dividedmanagements[m_finalclassifier.FindFeatBin(classifier,itr->m_features[classifier])].m_samples.push_back(&(*itr));
	}
}

//void AABoost::Managements2Samples()
//{
//	m_allsamples.clear();
//
//	DividedManagements::iterator itr;
//	for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
//	{
//		PSamples::iterator sitr;
//		for(sitr=itr->m_samples.begin();sitr!=itr->m_samples.end();sitr++)
//		{
//			m_allsamples.push_back(**sitr);
//		}
//	}
//}

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
		m_besth.clear();
		for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
		{
			m_besth.push_back(itr->GetH());
		}

		m_bestclassifier=m_currentclassifier;
	}
	else
	{
		if(m_bestnormalizationfactor>normalizationfactor)
		{
			m_bestnormalizationfactor=normalizationfactor;

			//保存最优弱分类器输出
			m_besth.clear();
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

#ifdef DEBUG_OUTPUT
	m_totalprob=0;
	m_totalnum=0;
#endif

	for(itr=m_dividedmanagements.begin();itr!=m_dividedmanagements.end();itr++)
	{
		PSamples::iterator sitr;
		for(sitr=itr->m_samples.begin();sitr!=itr->m_samples.end();sitr++)
		{
			if((*sitr)->m_label==OneSample::POSITIVE)
			{
				(*sitr)->m_probability=(*sitr)->m_probability*exp(-1.0*(m_besth[(itr-m_dividedmanagements.begin())]))/m_bestnormalizationfactor;
			}
			else
			{
				(*sitr)->m_probability=(*sitr)->m_probability*exp(+1.0*(m_besth[(itr-m_dividedmanagements.begin())]))/m_bestnormalizationfactor;
			}

#ifdef DEBUG_OUTPUT
			m_totalprob+=(*sitr)->m_probability;
			m_totalnum++;
#endif

		}
	}
}

void AABoost::RunRealAdaboost(double maxfalsepositivesf,double minpassd,unsigned int maxweakclassifiernum)
{
	//连续Adaboost算法主循环

	//变量声明并初始化
	double falsepositivesf=maxfalsepositivesf+1;
	double passd=minpassd-1;

	//初始化
	Init();

	//设置BIN划分个数
	m_finalclassifier.SetBinsCount(24);

	m_finalclassifier.m_strongbestclassifier.clear();
	m_finalclassifier.m_strongbesth.clear();

	//计算所有类型的特征集合中的最大值和最小值
	m_finalclassifier.GetMinMaxFeat(m_allsamples);

	//初始化样本概率分布
	Samples::iterator sitr;
	for(sitr=m_allsamples.begin();sitr!=m_allsamples.end();sitr++)
	{
		sitr->InitProb(m_allsamples.size());
	}

	while(m_t<maxweakclassifiernum && falsepositivesf>maxfalsepositivesf)
	{
		//每次迭代开始
		//选择弱分类器前初始化
		InitWeak();

		//对所有特征进行划分并得到最优特征及对应弱分类器输出
		CLASSIFIER classifier;
		int percent=-1;
		for(classifier=0;classifier<m_finalclassifier.GetFeatTypesnum();classifier++)
		{
			//记录当前弱分类器
			m_currentclassifier=classifier;

			//对每一个类型特征，进行样本划分
			Samples2Managements(classifier);

			//当前类型对应划分处理
			SelectBestNormalizationFactorAndH();

#ifdef DEBUG_OUTPUT
			if(percent!=(int)((double)classifier/m_finalclassifier.GetFeatTypesnum()*100))
			{
				percent=(int)((double)classifier/m_finalclassifier.GetFeatTypesnum()*100);
				cout<<"\r进度:"<<setw(3)<<percent<<"% 当前归一化因子:"<<setw(8)<<m_bestnormalizationfactor;
			}
#endif
		}
#ifdef DEBUG_OUTPUT
		if(percent!=(int)((double)classifier/m_finalclassifier.GetFeatTypesnum()*100))
		{
			percent=(int)((double)classifier/m_finalclassifier.GetFeatTypesnum()*100);
			cout<<"\r进度:"<<setw(3)<<percent<<"% 当前归一化因子:"<<setw(8)<<m_bestnormalizationfactor<<endl;
		}
#endif

		//更新样本概率分布(注意:更新前要进行样本最优划分)
		Samples2Managements(m_bestclassifier);
		UpdateProbabilityDistribution();

		//更新所有样本
		//Managements2Samples();

		//保存强分类器
		m_finalclassifier.m_strongbestclassifier.push_back(m_bestclassifier);
		m_finalclassifier.m_strongbesth.push_back(m_besth);

		//调整阈值，并计算当前强分类器误报率及通过率
		CalcFalseAndPass(falsepositivesf,passd,minpassd);

		m_t++;

#ifdef DEBUG_OUTPUT
		cout<<endl<<"当前弱分类器数:"<<m_finalclassifier.m_strongbestclassifier.size()<<endl;
		cout<<"当前划分中样本总数:"<<m_totalnum<<"  当前样本概率总和:"<<m_totalprob<<endl;
		cout<<"该层分类器输出值:";
		for(int i=0;i<m_besth.size();i++)
		{
			cout<<m_besth[i]<<" ";
		}
		cout<<endl;
		cout<<"当前正确率(正样本识别成人脸比例):"<<passd<<endl;
		cout<<"当前错误率(负样本识别成人脸比例):"<<falsepositivesf<<endl<<endl;
#endif
	}
}

void AABoost::CalcFalseAndPass(double &falsepositivesf,double &passd,double minpassd)
{
	double signsum_pos=0;
	double signsum_neg=0;
	vector<double> v_pos;
	vector<double> v_neg;

	Samples::iterator sitr;
	for(sitr=m_allsamples.begin();sitr!=m_allsamples.end();sitr++)
	{
		signsum_pos=0;
		signsum_neg=0;
		vector<CLASSIFIER>::iterator citr;
		vector<vector<double> >::iterator hitr;
		for(citr=m_finalclassifier.m_strongbestclassifier.begin(),hitr=m_finalclassifier.m_strongbesth.begin();citr!=m_finalclassifier.m_strongbestclassifier.end() && hitr!=m_finalclassifier.m_strongbesth.end();citr++,hitr++)
		{
			if(sitr->m_label==OneSample::POSITIVE)
				signsum_pos+=hitr->at(m_finalclassifier.FindFeatBin(*citr,sitr->m_features[*citr]));
			else if(sitr->m_label==OneSample::NEGATIVE)
				signsum_neg+=hitr->at(m_finalclassifier.FindFeatBin(*citr,sitr->m_features[*citr]));
		}
		
		v_pos.push_back(signsum_pos);
		v_neg.push_back(signsum_neg);
	}

	//所有样本送入未设置阈值b的分类器，对输出进行排序
	sort(v_pos.begin(),v_pos.end());
	sort(v_neg.begin(),v_neg.end());

	unsigned int idx;
	double b;

	//设置阈值b
	idx=(unsigned int)((v_pos.size()-1)*(1-minpassd));
	b=v_pos.at(idx);
	m_finalclassifier.m_bestb=b;

	//计算通过率
	passd=(double)(v_pos.size()-idx)/v_pos.size();
	m_passd=passd;

	//计算错误率
	vector<double>::iterator negitr;
	for(negitr=v_neg.begin(),idx=0;negitr!=v_neg.end();negitr++,idx++)
	{
		if(*negitr>m_finalclassifier.m_bestb)
			break;
	}
	falsepositivesf=(double)(v_neg.size()-idx)/v_neg.size();
	m_falsepositivesf=falsepositivesf;
}

OneSample::LABELTYPE AABoost::Predict(const OneSample &onesample)
{
	if(m_finalclassifier.m_strongbestclassifier.size()!=m_finalclassifier.m_strongbesth.size() || m_finalclassifier.m_strongbestclassifier.size()==0 || m_finalclassifier.m_strongbesth.size()==0)
		return OneSample::UNKNOWN;

	vector<CLASSIFIER>::iterator citr;
	vector<vector<double> >::iterator hitr;
	double sign_num=0;
	for(citr=m_finalclassifier.m_strongbestclassifier.begin(),hitr=m_finalclassifier.m_strongbesth.begin();citr!=m_finalclassifier.m_strongbestclassifier.end() && hitr!=m_finalclassifier.m_strongbesth.end();citr++,hitr++)
	{
		sign_num+=hitr->at(m_finalclassifier.FindFeatBin(*citr,onesample.m_features[*citr]));
	}
	sign_num-=m_finalclassifier.m_bestb;
	if(sign_num>0)
		return OneSample::POSITIVE;
	else if(sign_num<0)
		return OneSample::NEGATIVE;
	else
		return OneSample::UNKNOWN;
}

void AABoost::Release()
{
	m_dividedmanagements.clear();
	m_allsamples.clear();
	m_besth.clear();
}

void AABoost::InsertOneSample(OneSample::LABELTYPE label,vector <double> &features,bool isFirst)
{
	if(isFirst==true)
		Release();

	OneSample onesample;
	onesample.m_label=label;
	onesample.m_features=features;

	m_allsamples.push_back(onesample);
}