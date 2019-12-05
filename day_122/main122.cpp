/*
OpenCV DNN 实现图像分类

使用ImageNet数据集支持1000分类的GoogleNet网络模型， 分别演示了Python与C++语言中的使用该模型实现图像分类标签预测。其中label标签是在一个单独的文本文件中读取，
模型从上面的链接中下载即可。读取模型的API：
Net cv::dnn::readNetFromCaffe(
	const String & 	prototxt,
	const String & 	caffeModel = String()
)
prototxt表示模型的配置文件
caffeModel表示模型的权重二进制文件

使用模型实现预测的时候，需要读取图像作为输入，网络模型支持的输入数据是四维的输入，所以要把读取到的Mat对象转换为四维张量，OpenCV的提供的API为如下：
Mat cv::dnn::blobFromImage(
	InputArray 	image,
	double 	scalefactor = 1.0,
	const Size & 	size = Size(),
	const Scalar & 	mean = Scalar(),
	bool 	swapRB = false,
	bool 	crop = false,
	int 	ddepth = CV_32F
)
image输入图像
scalefactor 默认1.0
size表示网络接受的数据大小
mean表示训练时数据集的均值
swapRB 是否互换Red与Blur通道
crop剪切
ddepth 数据类型

模型下载地址：
opencv_tutorial/data/models/googlenet at master · ...
模型说明：
opencv/samples/dnn at master · opencv/opencv · Git...
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

String labels_txt_file = "../models/inception5h/imagenet_comp_graph_label_strings.txt";
String tf_pb_file = "../models/inception5h/tensorflow_inception_graph.pb";
vector<String> readClassNames();
int main(int argc, char** argv) {
	Mat src = imread("../images/green.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	vector<String> labels = readClassNames();

	Mat rgb;
	cvtColor(src, rgb, COLOR_BGR2RGB);
	int w = 224;
	int h = 224;

	// 加载网络
	Net net = readNetFromTensorflow(tf_pb_file);
	if (net.empty()) {
		printf("read caffe model data failure...\n");
		return -1;
	}
	Mat inputBlob = blobFromImage(src, 1.0f, Size(224, 224), Scalar(), true, false);
	inputBlob -= 117.0; // 均值

						// 执行图像分类
	Mat prob;
	net.setInput(inputBlob, "input");
	prob = net.forward("softmax2");

	// 得到最可能分类输出
	Mat probMat = prob.reshape(1, 1);
	Point classNumber;
	double classProb;
	minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	int classidx = classNumber.x;
	printf("\n current image classification : %s, possible : %.2f", labels.at(classidx).c_str(), classProb);

	// 显示文本
	putText(src, labels.at(classidx), Point(20, 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8);
	imshow("Image Classification", src);
	imwrite("D:/result.png", src);
	waitKey(0);
	destroyAllWindows();

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
