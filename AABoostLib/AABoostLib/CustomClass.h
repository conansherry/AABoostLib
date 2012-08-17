#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H

#include <vector>
#include <stdint.h>

using namespace std;

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
	uint32_t m_partition;
	double m_probability;
	vector<double> m_features;
};

typedef vector<OneSample> Samples;

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

	//������������Output
	void CalcOutput();

	//�����������Output
	double GetOutput();

	//����ƽ������
	void SetSmoothingFactor(double value);

	//����
public:
	Samples m_samples;

private:
	double m_probposw;
	double m_probnegw;
	double m_output;
	double m_smoothingfactor;
};

typedef vector<DividedManagement> DividedManagements;
typedef uint32_t CLASSIFIER;

class AABoost
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
	void CalcBestNormalizationFactor();

	//���¸��ʷֲ�
	void UpdateProbabilityDistribution();

	//����
private:
	CLASSIFIER m_bestclassifier;
	CLASSIFIER m_currentclassifier;
	uint32_t m_binscount;
	double m_bestnormalizationfactor;

	DividedManagements m_dividedmanagements;
	Samples m_allsamples;
};

#endif