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

	//设置初始参数
	void SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives);

	//载入样本
	void LoadSamples();

	//训练
	void LevelTrain();

	//每层训练完毕+重新整理负样本
	void LevelTrainFinished();

	//属性
private:
	UINT m_i;
	double m_Fi;

	double m_maxfalsepositivesf;
	double m_minpassd;
	double m_targetfalsepositivesf;
};

#endif