#ifndef FALLSDETECTOR_H
#define FALLSDETECTOR_H

#include "Common.h"
#include "RealAdaboost.h"

class FallsDetector
{
	//��Ϊ
public:
	FallsDetector();
	~FallsDetector();

	//���ó�ʼ����
	void SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives);

	//��������
	void LoadSamples();

	//ѵ��
	void LevelTrain();

	//ÿ��ѵ�����+������������
	void LevelTrainFinished();
	
	void CreateCascadeClassifier();

	//����
private:
	UINT m_i;		//i
	double m_fi;	//Fi

	double m_maxfalsepositivesf;
	double m_minpassd;
	double m_targetfalsepositivesf;

	PosSamples m_possamples;
	NegSamples m_negsamples;

	AABoost m_aaboost;
};

#endif