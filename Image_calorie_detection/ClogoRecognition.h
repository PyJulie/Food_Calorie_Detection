#pragma once
#include <opencv/cv.h>
#include <opencv\highgui.h>
#include <opencv\ml.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
using namespace cv;
class ClogoRecognition
{
public:
	ClogoRecognition();
	bool svmTrain();
	int svmTest(string filename);
	bool svmTest();
	bool createTrainSamDescribeTxt();
	bool createTestSamDescribeTxt();
	~ClogoRecognition();
};

