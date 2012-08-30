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

	//��ʼ��
	void Init();

	//���ó�ʼ����
	void SetInitParameters(double maxfalsepositives,double minpass);
	void SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives,UINT maxweakclassifiernum);

	//��������
	void LoadSamples();

	//ѵ��
	void LevelTrain();

	//ÿ��ѵ�����+������������
	void LevelTrainFinished();
	
	//��������ǿ������
	void CreateCascadeClassifier();

	//����
private:
	UINT m_i;		//i
	double m_fi;	//Fi

	double m_maxfalsepositivesf;
	double m_minpassd;
	double m_targetfalsepositivesf;
	UINT m_maxweakclassifiernum;

	PosSamples m_possamples;
	NegSamples m_negsamples;

	AABoost m_aaboost;
	vector<AABoost> m_cascadeclassifier;
};

#endif