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

	//����
public:
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

	void CalcProbW();
	void GetProbW();
	void CalcOutput();
	void GetOutput();

	//����
public:
	vector<OneSample> m_samples;

private:
	double m_probposw;
	double m_probnegw;
	double m_output;
};

#endif