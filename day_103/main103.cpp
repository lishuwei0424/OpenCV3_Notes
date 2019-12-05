/*
HOG特征描述子 – 使用描述子特征生成样本数据

对于HOG特征，我们可以通过预先训练的特征数据，进行多尺度的对象检测，OpenCV中基于HOG的行人检测是一个典型案例，同时我们还可以实现自定义对象的检测，这种自定义对象检测，可以分为两个部分，
第一部分：通过提取样本的HOG描述子，生成样本的特征数据，第二部分通过SVM进行分类学习与训练，保存为模型。这样我们以后就可以通过模型来实现自定义对象检测啦。今天我们分享第二部分，使用HOG
描述子特征数据生成数据集，进行SVM分类训练，实现对象分类识别。
这里我已一个很常见的应用，电表检测为例，这类问题早期主要通过特征匹配实现，但是这个方法比较容易受到各种因素干扰，不是很好，通过提取HOG特征、进行SVM特征分类、然后开窗检测，是一个很好的解
决方法。
在OpenCV中训练SVM模型，其数据格式常见的是“行模式”就是一行（多列向量）是一个样本，对应一个整数标签(label)。这里采用默认的窗口大小为64x128 提取HOG特征向量，得到的每个样本的向量数目等于
7x15x36=3780，有多少个样本就有多少行， 对于的标签是每一行对应自己的标签，有多少个训练样本，标签就有多少行！
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

string positive_dir = "../dataset/elec_watch/elec_watch/positive/";
string negative_dir = "../dataset/elec_watch/elec_watch/negative/";
void get_hog_descripor(Mat &image, vector<float> &desc);
void generate_dataset(Mat &trainData, Mat &labels);

int main(int argc, char** argv) {
	Mat trainData = Mat::zeros(Size(3780, 26), CV_32FC1);
	Mat labels = Mat::zeros(Size(1, 26), CV_32SC1);
	generate_dataset(trainData, labels);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

void get_hog_descripor(Mat &image, vector<float> &desc) {
	HOGDescriptor hog;
	int h = image.rows;
	int w = image.cols;
	float rate = 64.0 / w;
	Mat img, gray;
	resize(image, img, Size(64, int(rate*h)));
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat result = Mat::zeros(Size(64, 128), CV_8UC1);
	result = Scalar(127);
	Rect roi;
	roi.x = 0;
	roi.width = 64;
	roi.y = (128 - gray.rows) / 2;
	roi.height = gray.rows;
	gray.copyTo(result(roi));
	hog.compute(result, desc, Size(8, 8), Size(0, 0));
}

void generate_dataset(Mat &trainData, Mat &labels) {
	vector<string> images;
	glob(positive_dir, images);
	int pos_num = images.size();
	for (int i = 0; i < images.size(); i++) {
		Mat image = imread(images[i].c_str());
		vector<float> fv;
		imshow("image", image);
		waitKey(0);
		get_hog_descripor(image, fv);
		printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
		for (int j = 0; j < fv.size(); j++) {
			trainData.at<float>(i, j) = fv[j];
		}
		labels.at<int>(i, 0) = 1;
	}

	images.clear();
	glob(negative_dir, images);
	for (int i = 0; i < images.size(); i++) {
		Mat image = imread(images[i].c_str());
		vector<float> fv;
		imshow("image", image);
		waitKey(0);
		get_hog_descripor(image, fv);
		printf("image path : %s, feature data length: %d \n", images[i].c_str(), fv.size());
		for (int j = 0; j < fv.size(); j++) {
			trainData.at<float>(i + pos_num, j) = fv[j];
		}
		labels.at<int>(i + pos_num, 0) = -1;
	}
}