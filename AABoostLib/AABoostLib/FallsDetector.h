#ifndef FALLSDETECTOR_H
#define FALLSDETECTOR_H

#include "Common.h"
#include "RealAdaboost.h"
#include <fstream>

class EXPORT_CLASS FallsDetector
{
	//��Ϊ
public:
	FallsDetector();
	~FallsDetector();

	//��������ǿ������
	void CreateCascadeClassifier(string posfile,string negfile);

	//���ó�ʼ����
	void SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives,unsigned int maxweakclassifiernum);

private:
	//��ʼ��
	void Init();

	//ѵ��
	void LevelTrain();

	//ÿ��ѵ�����+������������
	void LevelTrainFinished();

	//��ѡ����
	void PrepareSamples(string posfile,string negfile);

	//������������
	void LoadSamples(string posdata,string negdata);

	//�����������ļ�
	void SaveFeatures(ofstream &fout,vector<double> &features);

	//����
private:
	unsigned int m_i;		//i
	double m_fi;	//Fi

	double m_maxfalsepositivesf;
	double m_minpassd;
	double m_targetfalsepositivesf;
	unsigned int m_maxweakclassifiernum;

	PosSamples m_possamples;
	NegSamples m_negsamples;

	AABoost m_aaboost;
	vector<AABoost> m_cascadeclassifier;
};

#endif