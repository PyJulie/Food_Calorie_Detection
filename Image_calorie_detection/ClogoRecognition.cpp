#include "ClogoRecognition.h"


ClogoRecognition::ClogoRecognition()
{
}


ClogoRecognition::~ClogoRecognition()
{
}
bool ClogoRecognition::svmTrain()
{
	vector<string> img_path;//图像路径容器  
	vector<int> img_catg;//图像类别容器
	int nLine = 0;
	string buf;
	ifstream svm_data("D:/newdanta/2.txt");//训练样本图片的路径都写在这个txt文件中，使用bat批处理文件可以得到这个txt文件 
	if (!svm_data)
		return FALSE;
	unsigned long n;
	while (svm_data)//将训练样本文件依次读取进来    
	{
		if (getline(svm_data, buf))
		{
			nLine++;
			if (nLine % 2 == 0)//注：奇数行是图片全路径，偶数行是标签 
			{
				img_catg.push_back(atoi(buf.c_str()));//atoi将字符串转换成整型，标志(0,1，2，...，9)，注意这里至少要有两个类别，否则会出错    
			}
			else
			{
				img_path.push_back(buf);//图像路径    
			}
		}
	}
	svm_data.close();//关闭文件    
	CvMat *data_mat, *res_mat;
	int nImgNum = nLine / 2; //nImgNum是样本数量，只有文本行数的一半，另一半是标签     
	data_mat = cvCreateMat(nImgNum, 432, CV_32FC1);  //第二个参数，即矩阵的列是由下面的descriptors的大小决定的，可以由descriptors.size()得到，且对于不同大小的输入训练图片，这个值是不同的  
	cvSetZero(data_mat);
	//类型矩阵,存储每个样本的类型标志    
	res_mat = cvCreateMat(nImgNum, 1, CV_32FC1);
	cvSetZero(res_mat);
	IplImage* src;
	IplImage* trainImg = cvCreateImage(cvSize(40, 32), 8, 3);//需要分析的图片，这里车标的尺寸归一化至40*32，所以上面定义了432，如果要更改图片大小，可以先用debug查看一下descriptors是多少，然后设定好再运行    

															 //处理HOG特征  
	for (string::size_type i = 0; i != img_path.size(); i++)
	{
		src = cvLoadImage(img_path[i].c_str(), 1);
		if (src == NULL)
		{
			cout << " can not load the image: " << img_path[i].c_str() << endl;
			continue;
		}

		cout << " 处理： " << img_path[i].c_str() << endl;

		cvResize(src, trainImg);
		HOGDescriptor *hog = new HOGDescriptor(cvSize(40, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);//图片尺寸：40*32；block尺寸：16*16；cell尺寸：8*8；检测窗口的滑动步长：8*8；一个单元格内统计9个方向的梯度直方图
		vector<float>descriptors;//存放结果     
		hog->compute(trainImg, descriptors, Size(1, 1), Size(0, 0)); //Hog特征计算      
		cout << "HOG dims: " << descriptors.size() << endl;
		n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(data_mat, i, n, *iter);//存储HOG特征 
			n++;
		}
		cvmSet(res_mat, i, 0, img_catg[i]);
		cout << " 处理完毕: " << img_path[i].c_str() << " " << img_catg[i] << endl;
	}


	//    CvSVM svm = CvSVM();//新建一个SVM     
	CvSVM svm;
	CvSVMParams param;//这里是SVM训练相关参数  
	CvTermCriteria criteria;
	criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);
	param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria);
	//        param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.3, 1.0, 5, 0.5, 1.0, NULL, criteria);
	svm.train(data_mat, res_mat, NULL, NULL, param);//训练数据     
													//保存训练好的分类器      
	svm.save("main.xml");
	cvReleaseMat(&data_mat);
	cvReleaseMat(&res_mat);
	cvReleaseImage(&trainImg);
	return TRUE;
}

int ClogoRecognition::svmTest(string filename) {
	double count = 0;
	string buf;
	CvSVM svm;
	svm.load("main.xml");//加载训练好的xml文件
						 //检测样本    
	IplImage *test;
	char result[512];


	
	
		test = cvLoadImage(filename.c_str(), 1);

		IplImage* trainTempImg = cvCreateImage(cvSize(40, 32), 8, 3);
		cvZero(trainTempImg);
		cvResize(test, trainTempImg);
		HOGDescriptor *hog = new HOGDescriptor(cvSize(40, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
		vector<float>descriptors;//结果数组       
		hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0));
		cout << "HOG dims: " << descriptors.size() << endl;
		CvMat* SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);
		int n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(SVMtrainMat, 0, n, *iter);
			n++;
		}

		int ret = svm.predict(SVMtrainMat);//检测结果
		if (ret == 2) {
			count++;
		}
		
	
	cvReleaseImage(&test);
	return ret;
}

bool ClogoRecognition::svmTest()
{
	double count = 0;
	string buf;
	CvSVM svm;
	svm.load("main.xml");//加载训练好的xml文件
						 //检测样本    
	IplImage *test;
	char result[512];
	vector<string> img_tst_path;
	ifstream img_tst("D:/testcaomei/2.txt");  //加载需要预测的图片集合，这个文本里存放的是图片全路径，不要标签
	if (!img_tst)
		return FALSE;
	while (img_tst)
	{
		if (getline(img_tst, buf))
		{
			img_tst_path.push_back(buf);
		}
	}
	img_tst.close();

	ofstream predict_txt("predict.txt");//把预测结果存储在这个文本中   
	for (string::size_type j = 0; j != img_tst_path.size(); j++)//依次遍历所有的待检测图片    
	{
		test = cvLoadImage(img_tst_path[j].c_str(), 1);
		if (test == NULL)
		{
			cout << " can not load the image: " << img_tst_path[j].c_str() << endl;
			continue;//结束本次循环
		}
		IplImage* trainTempImg = cvCreateImage(cvSize(40, 32), 8, 3);
		cvZero(trainTempImg);
		cvResize(test, trainTempImg);
		HOGDescriptor *hog = new HOGDescriptor(cvSize(40, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
		vector<float>descriptors;//结果数组       
		hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0));
		cout << "HOG dims: " << descriptors.size() << endl;
		CvMat* SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);
		int n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(SVMtrainMat, 0, n, *iter);
			n++;
		}

		int ret = svm.predict(SVMtrainMat);//检测结果
		if (ret == 2) {
			count++;
		}
		sprintf(result, "%s  %d\r\n", img_tst_path[j].c_str(), ret);
		predict_txt << result;  //输出检测结果到文本
	}
	cout << count / 600;
	predict_txt.close();
	cvReleaseImage(&test);
	return TRUE;
}

bool ClogoRecognition::createTrainSamDescribeTxt()
{
	string s;
	ifstream in("D:/newdanta/1.txt");
	if (!in)
		return FALSE;
	ofstream out;
	out.open("D:/newdanta/2.txt", ios::trunc); //ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则创建
	while (getline(in, s))//逐行读取数据并存于s中，直至数据全部读取
	{
		out << "D:/newdanta/" << s.c_str() << '\n';//路径后面加上训练样本的filename
		int n = s.c_str()[0] - '0';//每个训练样本文件都以数字开头命令，数字即代表该文件的类别
		out << n << '\n';//每个样本的后面写入其类别，用于SVM训练时指定type
	}
	in.close();
	out.close();
	return TRUE;
}
/*创建测试样本描述文件*/
bool ClogoRecognition::createTestSamDescribeTxt()
{
	string s;
	ifstream in("D:/testcaomei/1.txt");
	if (!in)
		return FALSE;
	ofstream out;
	out.open("D:/testcaomei/2.txt", ios::trunc); //ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则创建
	while (getline(in, s))//逐行读取数据并存于s中，直至数据全部读取
	{
		out << "D:/testcaomei/" << s.c_str() << '\n';//路径后面加上测试样本的filename
	}
	in.close();
	out.close();
	return TRUE;
}