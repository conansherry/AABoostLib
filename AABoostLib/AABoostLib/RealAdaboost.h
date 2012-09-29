#ifndef REALADABOOST_H
#define REALADABOOST_H

#include "Common.h"

class EXPORT_CLASS OneSample
{
	//��Ϊ
public:
	OneSample();
	~OneSample();

	//��ʼ���������ʷֲ�
	void InitProb(unsigned int samplesNum);

	//����
public:
	enum LABELTYPE{NEGATIVE=-1,UNKNOWN=0,POSITIVE=1};

	LABELTYPE m_label;
	int m_partition;
	double m_probability;
	vector<double> m_features;
};

typedef vector<OneSample> Samples;
typedef vector<OneSample* > PSamples;
typedef Samples PosSamples;
typedef Samples NegSamples;

class EXPORT_CLASS LUT
{
	//��Ϊ
public:
	LUT();
	~LUT();

	//��ȡ���������е���Сֵ���ֵ
	void GetMinMaxFeat(Samples &allsamples);

	//���û�ȡbinscount
	void SetBinsCount(int binscount);
	int GetBinsCount();

	//��ȡ��������BINS
	int FindFeatBin(CLASSIFIER classifier,double feature);

	//���û�ȡ������������
	void SetFeatTypesnum(unsigned int value);
	unsigned int GetFeatTypesnum();

	//����
protected:
	int m_binscount;
	unsigned int m_feattypesnum;
	vector<double> m_min;
	vector<double> m_max;
};

class EXPORT_CLASS Classifier:public LUT
{
public:
	Classifier(){}
	~Classifier(){}

	//ǿ����������
	double m_bestb;
	vector<CLASSIFIER> m_strongbestclassifier;
	vector<vector<double> > m_strongbesth;
};

class EXPORT_CLASS DividedManagement
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
	PSamples m_samples;

	//����
private:
	double m_probposw;
	double m_probnegw;
	double m_h;
	double m_smoothingfactor;
};

typedef vector<DividedManagement> DividedManagements;

class EXPORT_CLASS AABoost
{
	//��Ϊ
public:
	AABoost();
	~AABoost();

	//����Adaboost�㷨
	void RunRealAdaboost(double maxfalsepositivesf,double minpassd,unsigned int maxweakclassifiernum);

	//�ͷſռ�
	void Release();

	//ʹ�õ�ǰ������Ԥ����࣬����Ϊ��������������ֵΪ������
	OneSample::LABELTYPE Predict(const OneSample &onesample);

	//���������ӿ�
	void InsertOneSample(OneSample::LABELTYPE label,vector <double> &features,bool isFirst=false);

	//��Ϊ
private:
	//��ʼ��
	void Init();
	void InitWeak();

	//��������
	void Samples2Managements(CLASSIFIER classifier);

	//�������ʷֲ�������������
	//void Managements2Samples();

	//���㵱ǰ���ֹ�һ�����Ӳ�ѡȡ���Ž��
	void SelectBestNormalizationFactorAndH();

	//���¸��ʷֲ�
	void UpdateProbabilityDistribution();

	//����ǿ���������ʼ�ͨ����
	void CalcFalseAndPass(double &falsepositivesf,double &passd,double minpassd);

	//����
public:
	double m_falsepositivesf;
	double m_passd;

	Samples m_allsamples;

	Classifier m_finalclassifier;

	//����
private:
	CLASSIFIER m_bestclassifier;
	CLASSIFIER m_currentclassifier;
	unsigned int m_t;
	double m_bestnormalizationfactor;
	vector<double> m_besth;

	DividedManagements m_dividedmanagements;

#ifdef DEBUG_OUTPUT
	double m_totalprob;
	double m_totalnum;
#endif
};

#endif