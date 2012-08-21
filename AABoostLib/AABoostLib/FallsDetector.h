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

	//����
private:
	UINT m_i;
	double m_Fi;

	double m_maxfalsepositivesf;
	double m_minpassd;
	double m_targetfalsepositivesf;
};

#endif