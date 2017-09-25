#include "ClogoRecognition.h"


ClogoRecognition::ClogoRecognition()
{
}


ClogoRecognition::~ClogoRecognition()
{
}
bool ClogoRecognition::svmTrain()
{
	vector<string> img_path;//ͼ��·������  
	vector<int> img_catg;//ͼ���������
	int nLine = 0;
	string buf;
	ifstream svm_data("D:/newdanta/2.txt");//ѵ������ͼƬ��·����д�����txt�ļ��У�ʹ��bat�������ļ����Եõ����txt�ļ� 
	if (!svm_data)
		return FALSE;
	unsigned long n;
	while (svm_data)//��ѵ�������ļ����ζ�ȡ����    
	{
		if (getline(svm_data, buf))
		{
			nLine++;
			if (nLine % 2 == 0)//ע����������ͼƬȫ·����ż�����Ǳ�ǩ 
			{
				img_catg.push_back(atoi(buf.c_str()));//atoi���ַ���ת�������ͣ���־(0,1��2��...��9)��ע����������Ҫ��������𣬷�������    
			}
			else
			{
				img_path.push_back(buf);//ͼ��·��    
			}
		}
	}
	svm_data.close();//�ر��ļ�    
	CvMat *data_mat, *res_mat;
	int nImgNum = nLine / 2; //nImgNum������������ֻ���ı�������һ�룬��һ���Ǳ�ǩ     
	data_mat = cvCreateMat(nImgNum, 432, CV_32FC1);  //�ڶ���������������������������descriptors�Ĵ�С�����ģ�������descriptors.size()�õ����Ҷ��ڲ�ͬ��С������ѵ��ͼƬ�����ֵ�ǲ�ͬ��  
	cvSetZero(data_mat);
	//���;���,�洢ÿ�����������ͱ�־    
	res_mat = cvCreateMat(nImgNum, 1, CV_32FC1);
	cvSetZero(res_mat);
	IplImage* src;
	IplImage* trainImg = cvCreateImage(cvSize(40, 32), 8, 3);//��Ҫ������ͼƬ�����ﳵ��ĳߴ��һ����40*32���������涨����432�����Ҫ����ͼƬ��С����������debug�鿴һ��descriptors�Ƕ��٣�Ȼ���趨��������    

															 //����HOG����  
	for (string::size_type i = 0; i != img_path.size(); i++)
	{
		src = cvLoadImage(img_path[i].c_str(), 1);
		if (src == NULL)
		{
			cout << " can not load the image: " << img_path[i].c_str() << endl;
			continue;
		}

		cout << " ���� " << img_path[i].c_str() << endl;

		cvResize(src, trainImg);
		HOGDescriptor *hog = new HOGDescriptor(cvSize(40, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);//ͼƬ�ߴ磺40*32��block�ߴ磺16*16��cell�ߴ磺8*8����ⴰ�ڵĻ���������8*8��һ����Ԫ����ͳ��9��������ݶ�ֱ��ͼ
		vector<float>descriptors;//��Ž��     
		hog->compute(trainImg, descriptors, Size(1, 1), Size(0, 0)); //Hog��������      
		cout << "HOG dims: " << descriptors.size() << endl;
		n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(data_mat, i, n, *iter);//�洢HOG���� 
			n++;
		}
		cvmSet(res_mat, i, 0, img_catg[i]);
		cout << " �������: " << img_path[i].c_str() << " " << img_catg[i] << endl;
	}


	//    CvSVM svm = CvSVM();//�½�һ��SVM     
	CvSVM svm;
	CvSVMParams param;//������SVMѵ����ز���  
	CvTermCriteria criteria;
	criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);
	param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria);
	//        param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.3, 1.0, 5, 0.5, 1.0, NULL, criteria);
	svm.train(data_mat, res_mat, NULL, NULL, param);//ѵ������     
													//����ѵ���õķ�����      
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
	svm.load("main.xml");//����ѵ���õ�xml�ļ�
						 //�������    
	IplImage *test;
	char result[512];


	
	
		test = cvLoadImage(filename.c_str(), 1);

		IplImage* trainTempImg = cvCreateImage(cvSize(40, 32), 8, 3);
		cvZero(trainTempImg);
		cvResize(test, trainTempImg);
		HOGDescriptor *hog = new HOGDescriptor(cvSize(40, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
		vector<float>descriptors;//�������       
		hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0));
		cout << "HOG dims: " << descriptors.size() << endl;
		CvMat* SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);
		int n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(SVMtrainMat, 0, n, *iter);
			n++;
		}

		int ret = svm.predict(SVMtrainMat);//�����
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
	svm.load("main.xml");//����ѵ���õ�xml�ļ�
						 //�������    
	IplImage *test;
	char result[512];
	vector<string> img_tst_path;
	ifstream img_tst("D:/testcaomei/2.txt");  //������ҪԤ���ͼƬ���ϣ�����ı����ŵ���ͼƬȫ·������Ҫ��ǩ
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

	ofstream predict_txt("predict.txt");//��Ԥ�����洢������ı���   
	for (string::size_type j = 0; j != img_tst_path.size(); j++)//���α������еĴ����ͼƬ    
	{
		test = cvLoadImage(img_tst_path[j].c_str(), 1);
		if (test == NULL)
		{
			cout << " can not load the image: " << img_tst_path[j].c_str() << endl;
			continue;//��������ѭ��
		}
		IplImage* trainTempImg = cvCreateImage(cvSize(40, 32), 8, 3);
		cvZero(trainTempImg);
		cvResize(test, trainTempImg);
		HOGDescriptor *hog = new HOGDescriptor(cvSize(40, 32), cvSize(16, 16), cvSize(8, 8), cvSize(8, 8), 9);
		vector<float>descriptors;//�������       
		hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0));
		cout << "HOG dims: " << descriptors.size() << endl;
		CvMat* SVMtrainMat = cvCreateMat(1, descriptors.size(), CV_32FC1);
		int n = 0;
		for (vector<float>::iterator iter = descriptors.begin(); iter != descriptors.end(); iter++)
		{
			cvmSet(SVMtrainMat, 0, n, *iter);
			n++;
		}

		int ret = svm.predict(SVMtrainMat);//�����
		if (ret == 2) {
			count++;
		}
		sprintf(result, "%s  %d\r\n", img_tst_path[j].c_str(), ret);
		predict_txt << result;  //�����������ı�
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
	out.open("D:/newdanta/2.txt", ios::trunc); //ios::trunc��ʾ�ڴ��ļ�ǰ���ļ����,������д��,�ļ��������򴴽�
	while (getline(in, s))//���ж�ȡ���ݲ�����s�У�ֱ������ȫ����ȡ
	{
		out << "D:/newdanta/" << s.c_str() << '\n';//·���������ѵ��������filename
		int n = s.c_str()[0] - '0';//ÿ��ѵ�������ļ��������ֿ�ͷ������ּ�������ļ������
		out << n << '\n';//ÿ�������ĺ���д�����������SVMѵ��ʱָ��type
	}
	in.close();
	out.close();
	return TRUE;
}
/*�����������������ļ�*/
bool ClogoRecognition::createTestSamDescribeTxt()
{
	string s;
	ifstream in("D:/testcaomei/1.txt");
	if (!in)
		return FALSE;
	ofstream out;
	out.open("D:/testcaomei/2.txt", ios::trunc); //ios::trunc��ʾ�ڴ��ļ�ǰ���ļ����,������д��,�ļ��������򴴽�
	while (getline(in, s))//���ж�ȡ���ݲ�����s�У�ֱ������ȫ����ȡ
	{
		out << "D:/testcaomei/" << s.c_str() << '\n';//·��������ϲ���������filename
	}
	in.close();
	out.close();
	return TRUE;
}