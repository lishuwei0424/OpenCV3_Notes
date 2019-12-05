/*
OpenCV DNN单张与多张图像的推断

OpenCV DNN中支持单张图像推断，同时还支持分批次方式的图像推断，对应的两个相关API分别为blobFromImage与blobFromImages，它们的返回对象都是一个四维的Mat对象-按照顺序分别为NCHW 其组织方式详解如下：
N表示多张图像
C表示接受输入图像的通道数目
H表示接受输入图像的高度
W表示接受输入图像的宽度
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
参数解释
Images表示多张图像,image表示单张图像
Scalefactor表示放缩
Size表示图像大小
Mean表示均值
swapRB是否交换通道
crop是否剪切
ddepth 输出的类型，默认是浮点数格式
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

	// 加载网络
	Net net = readNetFromCaffe(protxt, bin_model);
	net.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
	net.setPreferableTarget(DNN_TARGET_CPU);

	if (net.empty()) {
		printf("read caffe model data failure...\n");
		return -1;
	}
	Mat inputBlob = blobFromImages(images, 1.0, Size(w, h), Scalar(104, 117, 123), false, false);

	// 执行图像分类
	Mat prob;
	net.setInput(inputBlob);
	prob = net.forward();
	vector<double> times;
	double time = net.getPerfProfile(times);
	float ms = (time * 1000) / getTickFrequency();
	printf("current inference time : %.2f ms \n", ms);

	// 得到最可能分类输出
	for (int n = 0; n < prob.rows; n++) {
		Point classNumber;
		double classProb;
		Mat probMat = prob(Rect(0, n, 1000, 1)).clone();
		Mat result = probMat.reshape(1, 1);
		minMaxLoc(result, NULL, &classProb, NULL, &classNumber);
		int classidx = classNumber.x;
		printf("\n current image classification : %s, possible : %.2f\n", labels.at(classidx).c_str(), classProb);

		// 显示文本
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
