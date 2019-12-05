/*
OpenCV DNN���������ͼ����ƶ�

OpenCV DNN��֧�ֵ���ͼ���ƶϣ�ͬʱ��֧�ַ����η�ʽ��ͼ���ƶϣ���Ӧ���������API�ֱ�ΪblobFromImage��blobFromImages�����ǵķ��ض�����һ����ά��Mat����-����˳��ֱ�ΪNCHW ����֯��ʽ������£�
N��ʾ����ͼ��
C��ʾ��������ͼ���ͨ����Ŀ
H��ʾ��������ͼ��ĸ߶�
W��ʾ��������ͼ��Ŀ��
Mat cv::dnn::blobFromImage(
	InputArray 	image,
	double 	scalefactor = 1.0,
	const Size & 	size = Size(),
	const Scalar & 	mean = Scalar(),
	bool 	swapRB = false,
	bool 	crop = false,
	int 	ddepth = CV_32F
)

Mat cv::dnn::blobFromImages(
	InputArrayOfArrays 	images,
	double 	scalefactor = 1.0,
	Size 	size = Size(),
	const Scalar & 	mean = Scalar(),
	bool 	swapRB = false,
	bool 	crop = false,
	int 	ddepth = CV_32F
)
��������
Images��ʾ����ͼ��,image��ʾ����ͼ��
Scalefactor��ʾ����
Size��ʾͼ���С
Mean��ʾ��ֵ
swapRB�Ƿ񽻻�ͨ��
crop�Ƿ����
ddepth ��������ͣ�Ĭ���Ǹ�������ʽ
*/

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>
/******************************************************
*
********************************************************/
using namespace cv;
using namespace cv::dnn;
using namespace std;


String bin_model = "../models/googlenet/bvlc_googlenet.caffemodel";
String protxt = "../models/googlenet/bvlc_googlenet.prototxt";
String labels_txt_file = "../models/googlenet/classification_classes_ILSVRC2012.txt";
vector<String> readClassNames();
int main(int argc, char** argv) {
	Mat image1 = imread("C:\\Users\\lishuwei\\Desktop\\OpenCV4.0.1_Projects\\OpenCV_DAY\\images\\cat.jpg");
	Mat image2 = imread("C:\\Users\\lishuwei\\Desktop\\OpenCV4.0.1_Projects\\OpenCV_DAY\\images\\aeroplane.jpg");
	vector<Mat> images;
	images.push_back(image1);
	images.push_back(image2);
	vector<String> labels = readClassNames();

	int w = 224;
	int h = 224;

	// ��������
	Net net = readNetFromCaffe(protxt, bin_model);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);

	if (net.empty()) {
		printf("read caffe model data failure...\n");
		return -1;
	}
	Mat inputBlob = blobFromImages(images, 1.0, Size(w, h), Scalar(104, 117, 123), false, false);

	// ִ��ͼ�����
	Mat prob;
	net.setInput(inputBlob);
	prob = net.forward();
	vector<double> times;
	double time = net.getPerfProfile(times);
	float ms = (time * 1000) / getTickFrequency();
	printf("current inference time : %.2f ms \n", ms);

	// �õ�����ܷ������
	for (int n = 0; n < prob.rows; n++) {
		Point classNumber;
		double classProb;
		Mat probMat = prob(Rect(0, n, 1000, 1)).clone();
		Mat result = probMat.reshape(1, 1);
		minMaxLoc(result, NULL, &classProb, NULL, &classNumber);
		int classidx = classNumber.x;
		printf("\n current image classification : %s, possible : %.2f\n", labels.at(classidx).c_str(), classProb);

		// ��ʾ�ı�
		putText(images[n], labels.at(classidx), Point(20, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8);
		imshow("Image Classification", images[n]);
		waitKey(0);
	}
	return 0;
}

std::vector<String> readClassNames()
{
	std::vector<String> classNames;

	std::ifstream fp(labels_txt_file);
	if (!fp.is_open())
	{
		printf("could not open file...\n");
		exit(-1);
	}
	std::string name;
	while (!fp.eof())
	{
		std::getline(fp, name);
		if (name.length())
			classNames.push_back(name);
	}
	fp.close();
	return classNames;
}
