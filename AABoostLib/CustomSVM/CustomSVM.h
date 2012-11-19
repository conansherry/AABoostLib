#ifndef CUSTOMSVM_H
#define CUSTOMSVM_H

#include "Common.h"
#include "svm.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

typedef struct svmnodedata
{
	int index;
	double value;
}SvmNodeData;

class EXPORT_CLASS CustomSVM
{
	//行为
public:
	CustomSVM();
	~CustomSVM();

	void Init(string input,string output,int predict_probability);

	void Predict();
	void Predict(vector<SvmNodeData>data,double &label,double &probability);

	int LoadModel(string modelpath);

	void Clear();

	//行为
private:
	char *Readline(FILE *input);
	void ExitInputError(int line_num);

	//属性
private:
	int m_predict_probability;
	int m_max_nr_attr;
	char *m_line;
	int m_max_line_len;
	struct svm_model *m_model;
	struct svm_node *m_x;
	FILE *m_input;
	FILE *m_output;
};

#endif