#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H

#include <vector>
#include <stdint.h>

using namespace std;

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

	int8_t m_label;
	uint32_t m_partition;
	double m_probability;
	vector<double> m_features;
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

	//计算弱分类器Output
	void CalcOutput();

	//获得弱分类器Output
	double GetOutput();

	//设置平滑因子
	void SetSmoothingFactor(double value);

	//属性
public:
	vector<OneSample> m_samples;

private:
	double m_probposw;
	double m_probnegw;
	double m_output;
	double m_smoothingfactor;
};

typedef vector<DividedManagement> DividedManagements;

class AABoost
{
	//行为
public:
	AABoost();
	~AABoost();

	//划分样本
	void Samples2Managements();

	//样本概率分布变更后更新样本
	void Managements2Samples();

	//属性
private:
	DividedManagements m_dividedmanagements;
	vector<OneSample> m_allsamples;
	uint32_t m_bestclassifier;
};

#endif