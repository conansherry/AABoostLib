#include "FallsDetector.h"
#include <iostream>
#include <time.h>

using namespace std;

class A{
public:
	A(){}
	vector<int> a;
};

int main(int argc,char *argv[])
{
	//BackGround background;
	//background.GetBackground("D:/WorkPlace/samples/neg/bg.txt","D:/WorkPlace/samples/neg_samples/");
	FallsDetector fallsdetector;
	fallsdetector.SetInitParameters(0.6,0.999,0.1,40);
	fallsdetector.CreateCascadeClassifier("D:/WorkPlace/samples/pos_samples/pos.txt","D:/WorkPlace/samples/neg_folder/neg.txt");
	system("pause");
	return 0;
}