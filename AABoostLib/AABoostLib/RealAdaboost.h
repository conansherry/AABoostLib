#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H

#include "Common.h"

class OneSample
{
	//行为
public:
	OneSample();
	~OneSample();

	//初始化样本概率分布
	void InitProb(unsigned int samplesNum);

	//属性
public:
	enum LABELTYPE{NEGATIVE=-1,POSITIVE=1};

	LABELTYPE m_label;
	INT m_partition;
	double m_probability;
	vector<double> m_features;
};

typedef vector<OneSample> Samples;

class LUT
{
	//行为
public:
	LUT();
	~LUT();

	//获取特征集合中的最小值最大值
	void GetMinMaxFeat(Samples &allsamples);

	//设置获取binscount
	void SetBinsCount(INT binscount);
	INT GetBinsCount();

	//获取特征所属BINS
	INT FindFeatBin(CLASSIFIER classifier,double feature);

	//属性
protected:
	INT m_binscount;
	vector<double> m_min;
	vector<double> m_max;
};

class DividedManagement
{
	//行为
public:
	DividedManagement();
	~DividedManagement();

	//计算ProbW
	void CalcProbW();

	//获得ProbW
	double GetProbPosW();
	double GetProbNegW();

	//计算弱分类器输出
	void CalcH();

	//获得弱分类器输出
	double GetH();

	//设置平滑因子
	void SetSmoothingFactor(double value);

	//属性
public:
	Samples m_samples;

	//属性
private:
	double m_probposw;
	double m_probnegw;
	double m_h;
	double m_smoothingfactor;
};

typedef vector<DividedManagement> DividedManagements;

class AABoost:public LUT
{
	//行为
public:
	AABoost();
	~AABoost();

	//划分样本
	void Samples2Managements(CLASSIFIER classifier);

	//样本概率分布变更后更新样本
	void Managements2Samples();

	//计算当前划分归一化因子并选取最优结果
	void SelectBestNormalizationFactor();

	//更新概率分布
	void UpdateProbabilityDistribution();

	//连续Adaboost算法
	void RunRealAdaboost();

	//属性
public:
	DividedManagements m_dividedmanagements;
	Samples m_allsamples;

	//属性
private:
	CLASSIFIER m_bestclassifier;
	CLASSIFIER m_currentclassifier;
	double m_bestnormalizationfactor;
};

#endif