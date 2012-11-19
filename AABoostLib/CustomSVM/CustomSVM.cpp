#include "CustomSVM.h"

CustomSVM::CustomSVM()
{
	//¹¹Ôìº¯Êý
	Init("","",1);
}

CustomSVM::~CustomSVM()
{
	Clear();
}

void CustomSVM::Init(string input,string output,int predict_probability)
{
	if(input.empty())
		m_input=NULL;
	else
		m_input=fopen(input.c_str(),"r");

	if(output.empty())
		m_output=NULL;
	else
		m_output=fopen(output.c_str(),"w");
	
	m_max_nr_attr=64;

	m_predict_probability=predict_probability;

	m_model=NULL;

	m_x=(struct svm_node *)malloc(m_max_nr_attr*sizeof(struct svm_node));

	m_line=NULL;
	
	m_max_line_len=0;
}

int CustomSVM::LoadModel(string modelpath)
{
	m_model=svm_load_model(modelpath.c_str());

	if(m_model==NULL)
		return 0;
	else
		return 1;
}

void CustomSVM::Predict()
{
	int correct = 0;
	int total = 0;
	double error = 0;
	double sump = 0, sumt = 0, sumpp = 0, sumtt = 0, sumpt = 0;

	int svm_type=svm_get_svm_type(m_model);
	int nr_class=svm_get_nr_class(m_model);
	double *prob_estimates=NULL;
	int j;

	if(m_predict_probability)
	{
		if (svm_type==NU_SVR || svm_type==EPSILON_SVR)
			printf("Prob. model for test data: target value = predicted value + z,\nz: Laplace distribution e^(-|z|/sigma)/(2sigma),sigma=%g\n",svm_get_svr_probability(m_model));
		else
		{
			int *labels=(int *) malloc(nr_class*sizeof(int));
			svm_get_labels(m_model,labels);
			prob_estimates = (double *) malloc(nr_class*sizeof(double));
			fprintf(m_output,"labels");		
			for(j=0;j<nr_class;j++)
				fprintf(m_output," %d",labels[j]);
			fprintf(m_output,"\n");
			free(labels);
		}
	}

	m_max_line_len = 1024;
	m_line = (char *)malloc(m_max_line_len*sizeof(char));
	while(Readline(m_input) != NULL)
	{
		int i = 0;
		double target_label, predict_label;
		char *idx, *val, *label, *endptr;
		int inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0

		label = strtok(m_line," \t\n");
		if(label == NULL) // empty line
			ExitInputError(total+1);

		target_label = strtod(label,&endptr);
		if(endptr == label || *endptr != '\0')
			ExitInputError(total+1);

		while(1)
		{
			if(i>=m_max_nr_attr-1)	// need one more for index = -1
			{
				m_max_nr_attr *= 2;
				m_x = (struct svm_node *) realloc(m_x,m_max_nr_attr*sizeof(struct svm_node));
			}

			idx = strtok(NULL,":");
			val = strtok(NULL," \t");

			if(val == NULL)
				break;
			errno = 0;
			m_x[i].index = (int) strtol(idx,&endptr,10);
			if(endptr == idx || errno != 0 || *endptr != '\0' || m_x[i].index <= inst_max_index)
				ExitInputError(total+1);
			else
				inst_max_index = m_x[i].index;

			errno = 0;
			m_x[i].value = strtod(val,&endptr);
			if(endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
				ExitInputError(total+1);

			++i;
		}
		m_x[i].index = -1;

		if (m_predict_probability && (svm_type==C_SVC || svm_type==NU_SVC))
		{
			predict_label = svm_predict_probability(m_model,m_x,prob_estimates);
			fprintf(m_output,"%g",predict_label);
			for(j=0;j<nr_class;j++)
				fprintf(m_output," %g",prob_estimates[j]);
			fprintf(m_output,"\n");
		}
		else
		{
			predict_label = svm_predict(m_model,m_x);
			fprintf(m_output,"%g\n",predict_label);
		}

		if(predict_label == target_label)
			++correct;
		error += (predict_label-target_label)*(predict_label-target_label);
		sump += predict_label;
		sumt += target_label;
		sumpp += predict_label*predict_label;
		sumtt += target_label*target_label;
		sumpt += predict_label*target_label;
		++total;
	}
	if (svm_type==NU_SVR || svm_type==EPSILON_SVR)
	{
		printf("Mean squared error = %g (regression)\n",error/total);
		printf("Squared correlation coefficient = %g (regression)\n",
		       ((total*sumpt-sump*sumt)*(total*sumpt-sump*sumt))/
		       ((total*sumpp-sump*sump)*(total*sumtt-sumt*sumt))
		       );
	}
	else
		printf("Accuracy = %g%% (%d/%d) (classification)\n",
		       (double)correct/total*100,correct,total);
	if(m_predict_probability)
		free(prob_estimates);
}

void CustomSVM::Predict(vector<SvmNodeData>data,double &label,double &probability)
{
	int svm_type=svm_get_svm_type(m_model);
	int nr_class=svm_get_nr_class(m_model);
	double *prob_estimates=NULL;

	if(nr_class!=2)
	{
		label=0;
		probability=0;
		return;
	}

	if(m_x)
	{
		free(m_x);
	}
	m_x=(struct svm_node *)malloc(sizeof(struct svm_node)*data.size());

	for(int i=0;i<data.size();i++)
	{
		m_x[i].index=data[i].index;
		m_x[i].value=data[i].value;
	}

	if(m_predict_probability && (svm_type==C_SVC || svm_type==NU_SVC))
	{
		label=svm_predict_probability(m_model,m_x,prob_estimates);
		probability=prob_estimates[0];
	}

	if(m_predict_probability)
		free(prob_estimates);
}

char *CustomSVM::Readline(FILE *input)
{
	int len;
	
	if(fgets(m_line,m_max_line_len,input) == NULL)
		return NULL;

	while(strrchr(m_line,'\n') == NULL)
	{
		m_max_line_len *= 2;
		m_line = (char *) realloc(m_line,m_max_line_len);
		len = (int) strlen(m_line);
		if(fgets(m_line+len,m_max_line_len-len,input) == NULL)
			break;
	}
	return m_line;
}

void CustomSVM::ExitInputError(int line_num)
{
	fprintf(stderr,"Wrong input format at line %d\n", line_num);
	exit(1);
}

void CustomSVM::Clear()
{
	if(m_model)
	{
		svm_free_and_destroy_model(&m_model);
		m_model=NULL;
	}

	if(m_x)
	{
		free(m_x);
		m_x=NULL;
	}

	if(m_line)
	{
		free(m_line);
		m_line=NULL;
	}

	fclose(m_input);

	fclose(m_output);
}