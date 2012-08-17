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

	int8_t m_label;
	uint32_t m_partition;
	double m_probability;
	vector<double> m_features;
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

	//������������Output
	void CalcOutput();

	//�����������Output
	double GetOutput();

	//����ƽ������
	void SetSmoothingFactor(double value);

	//����
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
	//��Ϊ
public:
	AABoost();
	~AABoost();

	//��������
	void Samples2Managements();

	//�������ʷֲ�������������
	void Managements2Samples();

	//����
private:
	DividedManagements m_dividedmanagements;
	vector<OneSample> m_allsamples;
	uint32_t m_bestclassifier;
};

#endif