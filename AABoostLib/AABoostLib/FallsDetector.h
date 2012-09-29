#ifndef FALLSDETECTOR_H
#define FALLSDETECTOR_H

#include "Common.h"
#include "RealAdaboost.h"
#include <fstream>

class EXPORT_CLASS FallsDetector
{
	//行为
public:
	FallsDetector();
	~FallsDetector();

	//创建级联强分类器
	void CreateCascadeClassifier(string posfile,string negfile);

	//设置初始参数
	void SetInitParameters(double maxfalsepositives,double minpass,double targetfalsepositives,unsigned int maxweakclassifiernum);

private:
	//初始化
	void Init();

	//训练
	void LevelTrain();

	//每层训练完毕+重新整理负样本
	void LevelTrainFinished();

	//挑选样本
	void PrepareSamples(string posfile,string negfile);

	//载入样本数据
	void LoadSamples(string posdata,string negdata);

	//保存特征到文件
	void SaveFeatures(ofstream &fout,vector<double> &features);

	//属性
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