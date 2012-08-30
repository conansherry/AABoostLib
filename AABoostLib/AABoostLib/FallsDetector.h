#ifndef FALLSDETECTOR_H
#define FALLSDETECTOR_H

#include "Common.h"
#include "RealAdaboost.h"

class FallsDetector
{
	//行为
public:
	FallsDetector();
	~FallsDetector();

	//初始化
	void Init();

	//设置初始参数
	void SetInitParameters(double maxfalsepositives,double minpass);
	void SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives,UINT maxweakclassifiernum);

	//载入样本
	void LoadSamples();

	//训练
	void LevelTrain();

	//每层训练完毕+重新整理负样本
	void LevelTrainFinished();
	
	//创建级联强分类器
	void CreateCascadeClassifier();

	//属性
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