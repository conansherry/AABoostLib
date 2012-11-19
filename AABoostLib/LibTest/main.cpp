#include "HogFeature.h"
#include "CustomSVM.h"
#include "BackGround.h"
#include "FallsDetector.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <opencv2/contrib/contrib.hpp>

using namespace std;

int main(int argc,char *argv[])
{
	//BackGround background;
	//background.GetBackground("D:/WorkPlace/samples/neg/bg.txt","D:/WorkPlace/training_73131/neg/neg_samples/",56,72);
	FallsDetector fallsdetector;
	fallsdetector.SetInitParameters(0.6,0.999,0.1,40);
	fallsdetector.CreateCascadeClassifier("D:/WorkPlace/samples/pos_samples/pos.txt","D:/WorkPlace/samples/neg_folder/neg.txt");

	//HogFeature hogfeature;
	//hogfeature.CreateHogDescriptor(cv::Size(24,24),cv::Size(4,4),cv::Size(2,2),cv::Size(2,2),9);
	//cv::Mat img=cv::imread("D:/WorkPlace/samples/test.bmp",0);
	//hogfeature.ExtractHaarFeatures(img);
/*--------------------------------------------------*/
	//HogFeature hogfeature;
	//hogfeature.CreateHogDescriptor(cv::Size(8,8),cv::Size(8,8),cv::Size(4,4),cv::Size(4,4),9);
	//unsigned int filetotal=0;
	//int FDim=hogfeature.GetFeaturesDim();
	//string filepath;
	//ifstream fin;

	//fin.open("D:/WorkPlace/training_73131/pos/pos.txt",ios_base::in);
	//vector<vector<double> > pos_features;
	//int tmpi;
	//tmpi=0;
	//while(getline(fin,filepath))
	//{
	//	cv::Mat tmp=cv::imread(filepath,0);
	//	cv::Mat img(56,72,tmp.type());
	//	cv::resize(tmp,img,cv::Size(img.cols,img.rows));
	//	hogfeature.ExtractHaarFeatures(img,cv::Size(4,4));

	//	if(filetotal==0)
	//	{
	//		filetotal=hogfeature.m_features.size()/FDim;
	//	}

	//	pos_features.push_back(hogfeature.m_features);
	//	printf("\r%8d",tmpi++);
	//}
	//fin.close();
	//printf("\n");

	//fin.open("D:/WorkPlace/training_73131/neg/neg.txt",ios_base::in);
	//vector<vector<double> > neg_features;
	//tmpi=0;
	//while(getline(fin,filepath))
	//{
	//	cv::Mat tmp=cv::imread(filepath,0);
	//	cv::Mat img(56,72,tmp.type());
	//	cv::resize(tmp,img,cv::Size(img.cols,img.rows));
	//	hogfeature.ExtractHaarFeatures(img,cv::Size(4,4));
	//	neg_features.push_back(hogfeature.m_features);
	//	printf("\r%8d",tmpi++);
	//}
	//fin.close();

	//ofstream fout;
	//string filename;
	//char numtmp[20];
	//vector<cv::LDA *> vlda;
	//for(int i=0;i<filetotal;i++)
	//{
	//	itoa(i,numtmp,10);
	//	filename.assign(numtmp);
	//	filename=filename+".data";

	//	//fstream hogout;
	//	//hogout.open("D:/WorkPlace/svmdata/"+filename,ios_base::out);
	//	//for(int j=0;j<pos_features.size();j++)
	//	//{
	//	//	hogout<<"+1 ";
	//	//	for(int k=0;k<FDim;k++)
	//	//		hogout<<k+1<<";"<<pos_features[j][i*FDim+k]<<" ";
	//	//	hogout<<endl;
	//	//}
	//	//for(int j=0;j<neg_features.size();j++)
	//	//{
	//	//	hogout<<"-1 ";
	//	//	for(int k=0;k<FDim;k++)
	//	//		hogout<<k+1<<";"<<neg_features[j][i*FDim+k]<<" ";
	//	//	hogout<<endl;
	//	//}
	//	//hogout.close();

	//	//cv::Mat train(pos_features.size()+neg_features.size(),FDim,CV_64FC1);
	//	//cv::Mat label(pos_features.size()+neg_features.size(),1,CV_64FC1);
	//	//for(int j=0;j<pos_features.size();j++)
	//	//{
	//	//	for(int k=0;k<FDim;k++)
	//	//		train.at<double>(j,k)=pos_features[j][i*FDim+k];
	//	//	label.at<double>(j,0)=1;
	//	//}
	//	//for(int j=0;j<neg_features.size();j++)
	//	//{
	//	//	for(int k=0;k<FDim;k++)
	//	//		train.at<double>(j+pos_features.size(),k)=neg_features[j][i*FDim+k];
	//	//	label.at<double>(j+pos_features.size(),0)=-1;
	//	//}

	//	//cv::LDA *lda=new cv::LDA(train,label);
	//	cv::LDA *lda=new cv::LDA();
	//	//lda->save("D:/WorkPlace/lda_result/"+filename);
	//	lda->load("D:/WorkPlace/lda_result/"+filename);
	//	vlda.push_back(lda);
	//}
	//cout<<endl<<"Features Dim:"<<vlda.size()<<endl;
	//ofstream dataout("D:/WorkPlace/samples/POSDATA2");
	//for(int i=0;i<pos_features.size();i++)
	//{
	//	for(int j=0;j<vlda.size();j++)
	//	{
	//		cv::Mat test(1,FDim,CV_64FC1);
	//		for(int k=0;k<FDim;k++)
	//		{
	//			test.at<double>(0,k)=pos_features[i][j*FDim+k];
	//		}
	//		cv::Mat result=vlda[j]->project(test);
	//		dataout<<result.at<double>(0,0)<<" ";
	//	}
	//}
	//dataout.close();

	//dataout.open("D:/WorkPlace/samples/NEGDATA2");
	//for(int i=0;i<neg_features.size();i++)
	//{
	//	for(int j=0;j<vlda.size();j++)
	//	{
	//		cv::Mat test(1,FDim,CV_64FC1);
	//		for(int k=0;k<FDim;k++)
	//		{
	//			test.at<double>(0,k)=neg_features[i][j*FDim+k];
	//		}
	//		cv::Mat result=vlda[j]->project(test);
	//		dataout<<result.at<double>(0,0)<<" ";
	//	}
	//}
	//dataout.close();
/*--------------------------------------------------*/
	//CustomSVM customsvm;
	//customsvm.Init("D:/WorkPlace/libsvm-3.12/heart_scale","D:/WorkPlace/libsvm-3.12/output.txt",1);
	//customsvm.LoadModel("D:/WorkPlace/libsvm-3.12/heart_scale.model");
	//customsvm.Predict();
	//customsvm.Clear();

	system("pause");
	return 0;
}