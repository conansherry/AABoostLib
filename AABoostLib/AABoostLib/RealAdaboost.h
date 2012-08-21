#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H

#include "Common.h"

class OneSample
{
	//��Ϊ
public:
	OneSample();
	~OneSample();

	//��ʼ���������ʷֲ�
	void InitProb(unsigned int samplesNum);

	//����
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
	//��Ϊ
public:
	LUT();
	~LUT();

	//��ȡ���������е���Сֵ���ֵ
	void GetMinMaxFeat(Samples &allsamples);

	//���û�ȡbinscount
	void SetBinsCount(INT binscount);
	INT GetBinsCount();

	//��ȡ��������BINS
	INT FindFeatBin(CLASSIFIER classifier,double feature);

	//����
protected:
	INT m_binscount;
	vector<double> m_min;
	vector<double> m_max;
};

class DividedManagement
{
	//��Ϊ
public:
	DividedManagement();
	~DividedManagement();

	//����ProbW
	void CalcProbW();

	//���ProbW
	double GetProbPosW();
	double GetProbNegW();

	//���������������
	void CalcH();

	//��������������
	double GetH();

	//����ƽ������
	void SetSmoothingFactor(double value);

	//����
public:
	Samples m_samples;

	//����
private:
	double m_probposw;
	double m_probnegw;
	double m_h;
	double m_smoothingfactor;
};

typedef vector<DividedManagement> DividedManagements;

class AABoost:public LUT
{
	//��Ϊ
public:
	AABoost();
	~AABoost();

	//��������
	void Samples2Managements(CLASSIFIER classifier);

	//�������ʷֲ�������������
	void Managements2Samples();

	//���㵱ǰ���ֹ�һ�����Ӳ�ѡȡ���Ž��
	void SelectBestNormalizationFactor();

	//���¸��ʷֲ�
	void UpdateProbabilityDistribution();

	//����Adaboost�㷨
	void RunRealAdaboost();

	//����
public:
	DividedManagements m_dividedmanagements;
	Samples m_allsamples;

	//����
private:
	CLASSIFIER m_bestclassifier;
	CLASSIFIER m_currentclassifier;
	double m_bestnormalizationfactor;
};

#endif